/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsPreproc.c
  �� �� ��   : ����
  ��    ��   : o00132663
  ��������   : 2011��12��28��
  ����޸�   :
  ��������   : TAF APSģ��״̬��Ԥ������ʵ���ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��12��28��
    ��    ��   : o00132663
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsCommonDef.h"
#include "Taf_Tafm_Remote.h"
#include "MnApsComm.h"
#include "MmaAppLocal.h"
#include "TafLog.h"
#include "TafApsCtx.h"
#include "TafApsProcNvim.h"
#include "TafAgentInterface.h"
#include "TafApsPreproc.h"
#include "TafApsComFunc.h"
#include "TafApsSndAt.h"
#include "ApsNdInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "TafApsSndL4a.h"
#include "MnApsMultiMode.h"
#endif
#include "TafSdcLib.h"
#include "TafApsProcIpFilter.h"
#include "TafApsApi.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "xcc_aps_pif.h"
#include "TafApsSndXcc.h"
#include "taf_aps_ppp_pif.h"
#include "xreg_aps_pif.h"
#include "hsm_aps_pif.h"
#include "TafApsSndHsm.h"
#endif

#include "TafMmaInterface.h"
#include "TafApsMntn.h"


#include "NasUsimmApi.h"
#include "NasComm.h"

#include "ehsm_aps_pif.h"
#include "taf_aps_dhcp_pif.h"
#include "TafApsSndCds.h"
#include "TafApsSndDhcp.h"
#include "TafApsSndEhsm.h"
#include "TafApsSndPpp.h"
#include "cnas_cttf_hrpd_pa_pif.h"

#include "TafApsProcUsim.h"

#include "TafApsProcEpdszid.h"
#include "TafApsSndInternalMsg.h"
#include "ApsCdsInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_PREPROC_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetDsFlowInfoReq_PreProc
 ��������  : AT��ϢID_MSG_TAF_PS_GET_DSFLOW_INFO_REQԤ������
 �������  : ulEventType - �¼���
             pstMsg      - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE    - ��Ϣ�������
             VOS_FALSE   - ��Ϣδ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetDsFlowInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstMsgHeader;
    TAF_PS_GET_DSFLOW_INFO_REQ_STRU    *pstGetDsFlowInfoReq;
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
    TAF_DSFLOW_QUERY_INFO_STRU          stDsFlowQryInfo;

    /* ��ʼ�� */
    pstMsgHeader        = (TAF_PS_MSG_STRU *)pstMsg;
    pstGetDsFlowInfoReq = (TAF_PS_GET_DSFLOW_INFO_REQ_STRU *)(pstMsgHeader->aucContent);

    /* �����ϱ���Ϣ��ʼ�� */
    PS_MEM_SET(&stDsFlowQryInfo, 0, sizeof(TAF_DSFLOW_QUERY_INFO_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

    /* ��ѯ����RAB���ص�������Ϣ */
    TAF_APS_QryAllRabDsFlowStats(&stDsFlowQryInfo);

    /* ��AT�ظ���ѯ����������Ϣ */
    TAF_APS_SndGetDsFlowInfoCnf(&(pstGetDsFlowInfoReq->stCtrl),
                                TAF_ERR_NO_ERROR,
                               &stDsFlowQryInfo);


    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtClearDsFlowReq_PreProc
 ��������  : AT��ϢID_MSG_TAF_PS_CLEAR_DSFLOW_REQԤ������
 �������  : ulEventType - �¼���
             pstMsg      - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32  - ����ִ�н��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��2��2��
    ��    ��   : A00165503
    �޸�����   : DTS2015021010050: ���������ֵ���ͳ��
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtClearDsFlowReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstMsgHeader;
    TAF_PS_CLEAR_DSFLOW_REQ_STRU       *pstClearDsFlowReq;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsflowCtx;


    /* ��ʼ�� */
    pstMsgHeader        = (TAF_PS_MSG_STRU*)pstMsg;
    pstClearDsFlowReq   = (TAF_PS_CLEAR_DSFLOW_REQ_STRU*)(pstMsgHeader->aucContent);

    /* �������RAB���ص�������Ϣ */
    TAF_APS_ClearAllRabDsFlowStats();

    /* ���AP�������ͳ�� */
    TAF_APS_ClearApDsFlowStats();

    /* �����������NV����ʹ�ܣ����NV������ʷ��Ϣ */
    pstApsDsflowCtx = TAF_APS_GetDsFlowCtxAddr();
    if (VOS_TRUE == pstApsDsflowCtx->ucDsFlowSave2NvFlg)
    {
        TAF_APS_ClearDsFlowInfoInNv();
    }

    /* ��AT�ظ���� */
    TAF_APS_SndClearDsFlowCnf(&(pstClearDsFlowReq->stCtrl),
                               TAF_ERR_NO_ERROR);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvConfigDsFlowRptReq_PreProc
 ��������  : AT��ϢID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_REQԤ������
 �������  : ulEventType - �¼���
             pstMsg      - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32  - ����ִ�н��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��11��09��
    ��    ��   : l00198894
    �޸�����   : Probe·�⹤�߶Խ���Ŀ�޸�AT�˿������ϱ���־λ
  3.��    ��   : 2013��4��8��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtConfigDsFlowRptReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstMsgHeader;
    TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU  *pstConfigDsFlowRptReq;
    /* Modified by s00217060 for �����ϱ�AT�������������C��, 2013-4-8, begin */
    VOS_UINT32                          ulRptCmdStatus;

    /* ��ʼ�� */
    pstMsgHeader            = (TAF_PS_MSG_STRU*)pstMsg;
    pstConfigDsFlowRptReq   = (TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU*)(pstMsgHeader->aucContent);

    /* ���µ����������������ϱ���ȫ�ֱ��� */
    if ( VOS_TRUE == pstConfigDsFlowRptReq->stReportConfigInfo.ulRptEnabled )
    {
        /* ����AT�˿������ϱ� */
        ulRptCmdStatus = VOS_TRUE;
    }
    else
    {
        /* ֹͣAT�˿������ϱ� */
        ulRptCmdStatus = VOS_FALSE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_DSFLOWRPT, ulRptCmdStatus);
    /* Modified by s00217060 for �����ϱ�AT�������������C��, 2013-4-8, end */

    /* ��AT�ظ������� */
    TAF_APS_SndConfigDsFlowRptCnf(&(pstConfigDsFlowRptReq->stCtrl),
                                  TAF_ERR_NO_ERROR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSetApDsFlowRptCfgReq_PreProc
 ��������  : ��ϢID_MSG_TAF_PS_SET_APDSFLOW_RPT_CFG_REQԤ������
 �������  : ulEventType --- �¼���
             pstMsg      --- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE    --- ��Ϣ�������
             VOS_FALSE   --- ��Ϣδ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��2��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSetApDsFlowRptCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_SET_APDSFLOW_RPT_CFG_REQ_STRU   *pstSetRptCfgReq = VOS_NULL_PTR;
    TAF_APS_DSFLOW_STATS_CTX_STRU          *pstDsFlowCtx    = VOS_NULL_PTR;
    TAF_PS_CAUSE_ENUM_UINT32                enCause;
    VOS_UINT32                              ulResult;

    pstSetRptCfgReq = (TAF_PS_SET_APDSFLOW_RPT_CFG_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    pstDsFlowCtx    = TAF_APS_GetDsFlowCtxAddr();

    if (VOS_TRUE == pstSetRptCfgReq->stRptCfg.ulRptEnabled)
    {
        /* ��ֵ����: KBYTE ---> BYTE */
        ulResult = VOS_64Multi32(0,                                             /* ulMultiplicandHigh */
                                 pstSetRptCfgReq->stRptCfg.ulFluxThreshold,     /* ulMultiplicandLow */
                                 TAF_APS_1_KBYTE_1024_BYTE,                     /* ulMultiplicator */
                                 &(pstDsFlowCtx->ulFluxThresHigh),              /* pulProductHigh */
                                 &(pstDsFlowCtx->ulFluxThresLow));              /* pulProductLow */
        if (VOS_OK == ulResult)
        {
            /* ����������ֵ�ϱ����� */
            pstDsFlowCtx->ulFluxThresRptFlg = VOS_TRUE;
            pstDsFlowCtx->ulFluxThresKByte  = pstSetRptCfgReq->stRptCfg.ulFluxThreshold;

            enCause                         = TAF_PS_CAUSE_SUCCESS;
        }
        else
        {
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvSetApDsFlowRptCfgReq_PreProc: VOS_64Multi32 failed.");

            enCause                         = TAF_PS_CAUSE_INVALID_PARAMETER;
        }
    }
    else
    {
        /* ����������ֵ�ϱ����� */
        pstDsFlowCtx->ulFluxThresRptFlg     = VOS_FALSE;
        pstDsFlowCtx->ulFluxThresKByte      = 0;
        pstDsFlowCtx->ulFluxThresHigh       = 0;
        pstDsFlowCtx->ulFluxThresLow        = 0;
        pstDsFlowCtx->ulTotalFluxHigh       = 0;
        pstDsFlowCtx->ulTotalFluxLow        = 0;

        enCause                             = TAF_PS_CAUSE_SUCCESS;
    }

    TAF_APS_SndSetApDsFlowRptCfgCnf(&(pstSetRptCfgReq->stCtrl), enCause);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvGetApDsFlowRptCfgReq_PreProc
 ��������  : ��ϢID_MSG_TAF_PS_GET_APDSFLOW_RPT_CFG_REQԤ������
 �������  : ulEventType --- �¼���
             pstMsg      --- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE    --- ��Ϣ�������
             VOS_FALSE   --- ��Ϣδ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��4��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvGetApDsFlowRptCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU   *pstGetRptCfgReq = VOS_NULL_PTR;
    TAF_APS_DSFLOW_STATS_CTX_STRU          *pstDsFlowCtx    = VOS_NULL_PTR;
    TAF_APDSFLOW_RPT_CFG_STRU               stRptCfg;

    pstGetRptCfgReq = (TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    pstDsFlowCtx    = TAF_APS_GetDsFlowCtxAddr();

    /* ��ȡAPDSFLOW���ò��� */
    stRptCfg.ulRptEnabled    = pstDsFlowCtx->ulFluxThresRptFlg;
    stRptCfg.ulFluxThreshold = pstDsFlowCtx->ulFluxThresKByte;

    TAF_APS_SndGetApDsFlowRptCfgCnf(&(pstGetRptCfgReq->stCtrl),
                                    TAF_PS_CAUSE_SUCCESS,
                                    &stRptCfg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSetDsFlowNvWriteCfgReq_PreProc
 ��������  : ��ϢID_MSG_TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQԤ������
 �������  : ulEventType --- �¼���
             pstMsg      --- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE    --- ��Ϣ�������
             VOS_FALSE   --- ��Ϣδ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSetDsFlowNvWriteCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU    *pstSetNvWriteCfgReq = VOS_NULL_PTR;
    TAF_APS_DSFLOW_STATS_CTX_STRU              *pstDsFlowCtx        = VOS_NULL_PTR;

    pstSetNvWriteCfgReq = (TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    pstDsFlowCtx        = TAF_APS_GetDsFlowCtxAddr();

    /* ��������дNV���� */
    if (VOS_TRUE == pstSetNvWriteCfgReq->stNvWriteCfg.ucEnabled)
    {
        /* ����дNV�����ѿ���, ���ݵ�ǰ����дNV�����Ƿ�������ͬ���� */
        if (VOS_TRUE == pstDsFlowCtx->ucDsFlowSave2NvFlg)
        {
            /* �������дNV���ڱ仯, ˢ�µ�ǰ������NV, ������ʱ�� */
            if (pstDsFlowCtx->ucDsFlowSavePeriod != pstSetNvWriteCfgReq->stNvWriteCfg.ucInterval)
            {
                pstDsFlowCtx->ucDsFlowSavePeriod = pstSetNvWriteCfgReq->stNvWriteCfg.ucInterval;

                TAF_APS_SaveDsFlowInfoToNv();

                TAF_APS_StopTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                                  TAF_APS_INVALID_PDPID);

                TAF_APS_StartTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                                   (pstDsFlowCtx->ucDsFlowSavePeriod * 60 * TIMER_S_TO_MS_1000),
                                   TAF_APS_INVALID_PDPID);
            }
        }
        /* ����дNV����δ����, ʹ������дNV����, ������ʱ�� */
        else
        {
            pstDsFlowCtx->ucDsFlowSave2NvFlg = VOS_TRUE;
            pstDsFlowCtx->ucDsFlowSavePeriod = pstSetNvWriteCfgReq->stNvWriteCfg.ucInterval;

            TAF_APS_StartTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                               (pstDsFlowCtx->ucDsFlowSavePeriod * 60 * TIMER_S_TO_MS_1000),
                               TAF_APS_INVALID_PDPID);
        }
    }
    /* �ر�����дNV���� */
    else
    {
        /* ����дNV�����ѿ���, ˢ�µ�ǰ������NV, ֹͣ��ʱ�� */
        if (VOS_TRUE == pstDsFlowCtx->ucDsFlowSave2NvFlg)
        {
            pstDsFlowCtx->ucDsFlowSave2NvFlg = VOS_FALSE;
            pstDsFlowCtx->ucDsFlowSavePeriod = pstSetNvWriteCfgReq->stNvWriteCfg.ucInterval;

            TAF_APS_SaveDsFlowInfoToNv();

            TAF_APS_StopTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                              TAF_APS_INVALID_PDPID);
        }
    }

    TAF_APS_SndSetDsFlowNvWriteCfgCnf(&(pstSetNvWriteCfgReq->stCtrl),
                                      TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvGetDsFlowNvWriteCfgReq_PreProc
 ��������  : ��ϢID_MSG_TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQԤ������
 �������  : ulEventType --- �¼���
             pstMsg      --- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE    --- ��Ϣ�������
             VOS_FALSE   --- ��Ϣδ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvGetDsFlowNvWriteCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU    *pstGetNvWriteCfgReq = VOS_NULL_PTR;
    TAF_APS_DSFLOW_STATS_CTX_STRU              *pstDsFlowCtx        = VOS_NULL_PTR;
    TAF_DSFLOW_NV_WRITE_CFG_STRU                stNvWriteCfg;

    pstGetNvWriteCfgReq = (TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    pstDsFlowCtx        = TAF_APS_GetDsFlowCtxAddr();

    /* ��ȡDSFLOWдNV���ò��� */
    PS_MEM_SET(&stNvWriteCfg, 0x00, sizeof(TAF_DSFLOW_NV_WRITE_CFG_STRU));
    stNvWriteCfg.ucEnabled  = pstDsFlowCtx->ucDsFlowSave2NvFlg;
    stNvWriteCfg.ucInterval = pstDsFlowCtx->ucDsFlowSavePeriod;

    TAF_APS_SndGetDsFlowNvWriteCfgCnf(&(pstGetNvWriteCfgReq->stCtrl),
                                      TAF_PS_CAUSE_SUCCESS,
                                      &stNvWriteCfg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiDsFlowReportExpired_PreProc
 ��������  : ���������ϱ���ʱ����ʱ��Ϣ
 �������  : ulEventType - �¼���
             pstMsg      - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ϣ�������
             VOS_FALSE - ��Ϣδ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��11��09��
    ��    ��   : l00198894
    �޸�����   : Probe·�⹤�߶Խ���Ŀ����OM�����ϱ�

  3.��    ��   : 2013��4��7��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���

  4.��    ��   : 2015��2��2��
    ��    ��   : A00165503
    �޸�����   : DTS2015021010050: ����������ֵ�ϱ�����

  5.��    ��   : 2016��01��21��
    ��    ��   : w00316404
    �޸�����   : DTS2016012006718: add cds state report for nonlte
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiDsFlowReportExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsflowCtx = VOS_NULL_PTR;
    TAF_CTRL_STRU                       stCtrl;
    TAF_DSFLOW_REPORT_STRU              stTotalDsFlowRptInfo;

    PS_MEM_SET(&stCtrl, 0x00, sizeof(TAF_CTRL_STRU));

    /* ��ȡDSFLOW������ */
    pstApsDsflowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* �����ǰ��PDP������� */
    if (VOS_FALSE == TAF_APS_CheckIfActiveRabIdExist())
    {
        return VOS_TRUE;
    }

    /* ��ʼ��������ѯ��Ϣ���� */
    PS_MEM_SET(&stTotalDsFlowRptInfo, 0, sizeof(TAF_DSFLOW_REPORT_STRU));

    /* ��ѯ���м���RAB���ص��ϱ�������Ϣ */
    TAF_APS_QryAllRabDsFlowReportInfo(&stTotalDsFlowRptInfo);

    pstApsDsflowCtx->ucDsFlowATRptTmrExpCnt = (pstApsDsflowCtx->ucDsFlowATRptTmrExpCnt + 1)
                                              % pstApsDsflowCtx->ucDsFlowATRptPeriod;

    if (0 == pstApsDsflowCtx->ucDsFlowATRptTmrExpCnt)
    {
        /* ��AT�ϱ�������Ϣ */
        stCtrl.ulModuleId    = WUEPS_PID_AT;
        stCtrl.usClientId    = MN_CLIENT_ID_BROADCAST;
        stCtrl.ucOpId        = 0;

        TAF_APS_SndDsFlowRptInd(&stCtrl, TAF_ERR_NO_ERROR, &stTotalDsFlowRptInfo);
    }

    if (VOS_TRUE == pstApsDsflowCtx->ucDsFlowOMReportFlg)
    {
        if (0 == pstApsDsflowCtx->ucDsFlowOMRptTmrExpCnt)
        {
            /* ��OM�ϱ�������Ϣ */
            TAF_APS_SndDsFlowOMRptInd(&stTotalDsFlowRptInfo);
        }

        pstApsDsflowCtx->ucDsFlowOMRptTmrExpCnt = (pstApsDsflowCtx->ucDsFlowOMRptTmrExpCnt + 1)
                                                  % pstApsDsflowCtx->ucDsFlowOMRptPeriod;
    }

    /* ������ֵ�ϱ����� */
    TAF_APS_ProcApDsFlowRpt();

    /* ���浱ǰ������Ϣ������ͳ��������ȫ�ֱ����������´ζ�ʱ����ʱ�������� */
    TAF_APS_UpdateAllRabCurrentFlowInfo();

    /* APSͳ�Ƶ�������MBΪ��λ�ģ�����Ҫת��ΪMb���� */
    TAF_APS_SwitchDdrRateByCurrentRate((stTotalDsFlowRptInfo.ulCurrentReceiveRate * 8),
                                       (stTotalDsFlowRptInfo.ulCurrentSendRate * 8));

    CDS_APS_CdsOmReport();

    /* ���������ϱ���ʱ��*/
    TAF_APS_StartTimer(TI_TAF_APS_DSFLOW_REPORT,
                       TI_TAF_APS_DSFLOW_REPORT_LEN,
                       TAF_APS_INVALID_PDPID);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiDsFlowReportExpired_PreProc
 ��������  : ������������NV��ʱ����ʱ��Ϣ
 �������  : ulEventType - �¼���
             pstMsg      - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ϣ�������
             VOS_FALSE - ��Ϣδ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��5��15��
    ��    ��   : A00165503
    �޸�����   : DTS2012051402688: Gģ�����������Ϣ�󲦺�����, ʱ��С��10��
                 ��, ��������ʱû�н�������Ϣд��NV
  3.��    ��   : 2012��5��30��
    ��    ��   : zhangyizhan 60575
    �޸�����   : DTS2012052907939, ���浽NV��ʱ����NV 9036����
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiDsFlowWriteNvExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsflowCtx;

    /* ��ʼ�� */
    pstApsDsflowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* ������ʷ������NVʹ�ܣ�����ʷ������Ϣ���浽NV�� */
    TAF_APS_SaveDsFlowInfoToNv();

    /* �жϱ�����ʷ������NV�Ƿ�ʹ�� */
    if (VOS_TRUE == pstApsDsflowCtx->ucDsFlowSave2NvFlg)
    {
        /* ����������ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                           (pstApsDsflowCtx->ucDsFlowSavePeriod * 60 * TIMER_S_TO_MS_1000),
                           TAF_APS_INVALID_PDPID);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetPrimPdpCtxInfoReq_PreProc
 ��������  : ��ѯ��PDP������Ԥ������
             (ID_MSG_TAF_PS_GET_PRIM_PDP_CONTEXT_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetPrimPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    (VOS_VOID)MN_APS_RcvGetPrimPdpCtxInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetPdpInfoReq_PreProc
 ��������  : ��ѯ����PDP������Ԥ������
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��5��
    ��    ��   : c00173809
    �޸�����   : DTS2012010604900
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetPdpInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                            *pstPsMsg;
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulPdpCtxInfoLen;
    VOS_UINT32                                  ulCidNum;
    TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU       *pstGetPdpCtxInfoReq;
    TAF_PS_GET_PDP_CONTEXT_INFO_CNF_STRU       *pstGetPdpCtxInfoCnf;

    /* ��ʼ����Ϣ */
    pstPsMsg            = (TAF_PS_MSG_STRU*)pstMsg;

    ulPdpCtxInfoLen     = 0;
    ulCidNum            = 0;
    pstGetPdpCtxInfoReq = (TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU*)pstPsMsg->aucContent;
    pstGetPdpCtxInfoCnf = VOS_NULL_PTR;

    /* �����¼����ݳ��� */
    ulPdpCtxInfoLen     = sizeof(TAF_PS_GET_PDP_CONTEXT_INFO_CNF_STRU);

    /* �����ڴ� */
    pstGetPdpCtxInfoCnf = (TAF_PS_GET_PDP_CONTEXT_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                WUEPS_PID_TAF,
                                ulPdpCtxInfoLen);

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstGetPdpCtxInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetPdpCtxInfoReq:  ERROR : PS_MEM_ALLOC Error!");
        return VOS_TRUE;
    }

    /* ��д�¼����� */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        /*��PDPû�ж���*/
        if (TAF_FREE == g_TafCidTab[ucIndex].ucUsed)
        {
            continue;
        }

        /* ����������PDP,ֻҪ�Ƕ���ľͷ��� */
        pstGetPdpCtxInfoCnf->ulCid[ulCidNum]    = ucIndex;
        ulCidNum++;
    }

    /* ��д�¼�����ͷ */
    pstGetPdpCtxInfoCnf->stCtrl     = pstGetPdpCtxInfoReq->stCtrl;
    pstGetPdpCtxInfoCnf->ulCidNum   = ulCidNum;
    pstGetPdpCtxInfoCnf->enCause    = TAF_PS_CAUSE_SUCCESS;

    /* ���ش����� */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_PDP_CONTEXT_INFO_CNF,
                    pstGetPdpCtxInfoCnf,
                    ulPdpCtxInfoLen);

    /* �ͷ����ڴ��PDP�����Ĳ������ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetPdpCtxInfoCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetSecPdpCtxInfoReq_PreProc
 ��������  : ��ѯ��PDP������Ԥ������
             (ID_MSG_TAF_PS_GET_SEC_PDP_CONTEXT_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetSecPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvGetSecPdpCtxInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetTftInfoReq_PreProc
 ��������  : ��ѯTFT����Ԥ������
             (ID_MSG_TAF_PS_GET_PDP_TFT_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetTftInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    (VOS_VOID)MN_APS_RcvGetTftInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetPdpIpAddrInfoReq_PreProc
 ��������  : ��ѯ�Ѽ�����ص�IP��ַ��������Ԥ������
             (ID_MSG_TAF_PS_GET_PDP_IP_ADDR_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetPdpIpAddrInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    (VOS_VOID)MN_APS_RcvGetPdpIpAddrInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetAnsModeInfoReq_PreProc
 ��������  : ��ѯPS����Զ�Ӧ��״̬Ԥ������
             (ID_MSG_TAF_PS_GET_ANSWER_MODE_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetAnsModeInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvGetAnsModeInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetPdpContextStateReq_PreProc
 ��������  : ��ѯ��ǰPDP�ļ���״̬

 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��06��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetPdpContextStateReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    (VOS_VOID)MN_APS_RcvGetPdpCtxStateReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}




#if ( FEATURE_ON == FEATURE_LTE )

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetDynamicPrimPdpCtxInfoReq_PreProc
 ��������  : ��ȡ��PDP�����Ķ�̬����Ԥ������
             (ID_MSG_TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetDynamicPrimPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ������Ϣ��L4A */
    TAF_APS_SndL4aSetCgcontrdpReq(pstPsMsg->aucContent);

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

    /* ����L4A��Ϣ�ظ�������ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* �����Ϣ���ȴ����� */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF,
                                     (VOS_UINT32 *)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetDynamicSecPdpCtxInfoReq_PreProc
 ��������  : ��ȡ��PDP�����Ķ�̬����Ԥ������
             (ID_MSG_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetDynamicSecPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ������Ϣ��L4A */
    TAF_APS_SndL4aSetCgscontrdpReq(pstPsMsg->aucContent);

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

    /* ����L4A��Ϣ�ظ�������ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* �����Ϣ���ȴ����� */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF,
                                     (VOS_UINT32 *)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetDynamicTftInfoReq_PreProc
 ��������  : ��ȡTFT�Ķ�̬����Ԥ������
             (ID_MSG_TAF_PS_GET_DYNAMIC_TFT_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetDynamicTftInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ������Ϣ��L4A */
    TAF_APS_SndL4aSetCgtftrdpReq(pstPsMsg->aucContent);

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));
    /* ����L4A��Ϣ�ظ�������ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* �����Ϣ���ȴ����� */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF,
                                     (VOS_UINT32 *)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetEpsQosInfoReq_PreProc
 ��������  : ��ѯEPS��������Ԥ������
             (ID_MSG_TAF_PS_GET_EPS_QOS_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetEpsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulErrCode;
    VOS_UINT32                          ulEqosInfoLen;
    VOS_UINT32                          ulCidNum;
    TAF_PS_MSG_STRU                    *pstPsMsg;
    TAF_PS_GET_EPS_QOS_INFO_REQ_STRU   *pstGetEqosInfoReq;
    TAF_PS_GET_EPS_QOS_INFO_CNF_STRU   *pstGetEqosInfoCnf;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (TAF_PS_MSG_STRU*)pstMsg;
    ulErrCode               = TAF_PARA_OK;
    ulEqosInfoLen           = 0;
    ulCidNum                = 0;
    pstGetEqosInfoReq       = (TAF_PS_GET_EPS_QOS_INFO_REQ_STRU*)pstPsMsg->aucContent;
    pstGetEqosInfoCnf       = VOS_NULL_PTR;

    /* �����¼����ݳ��� */
    ulEqosInfoLen     = sizeof(TAF_PS_GET_EPS_QOS_INFO_CNF_STRU)
                            + ((TAF_MAX_CID + 1) * sizeof(TAF_EPS_QOS_EXT_STRU));

    /* �����ڴ� */
    pstGetEqosInfoCnf = (TAF_PS_GET_EPS_QOS_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                WUEPS_PID_TAF,
                                ulEqosInfoLen);

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstGetEqosInfoCnf )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvAtGetEpsQosInfoReq_PreProc:  ERROR : PS_MEM_ALLOC Error!");
        return VOS_TRUE;
    }

    /* ��д�¼����� */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        PS_MEM_SET(&(pstGetEqosInfoCnf->astEpsQosInfo[ulCidNum]),
                   0x00,
                   sizeof(TAF_EPS_QOS_EXT_STRU));

        /* ��ȡEPS QOS��Ϣ */
        TAF_APS_QueEpsQosInfo(ucIndex, &(pstGetEqosInfoCnf->astEpsQosInfo[ulCidNum]), &ulErrCode);

        if ( TAF_PARA_OK == ulErrCode )
        {
            ulCidNum++;
        }
    }

    /* ��д�¼�����ͷ */
    pstGetEqosInfoCnf->stCtrl           = pstGetEqosInfoReq->stCtrl;
    pstGetEqosInfoCnf->ulCidNum         = ulCidNum;
    pstGetEqosInfoCnf->enCause          = TAF_PS_CAUSE_SUCCESS;

    /* ���ش����� */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_EPS_QOS_INFO_CNF,
                     pstGetEqosInfoCnf,
                     ulEqosInfoLen);

    /* �ͷ����ڴ��PDP�����Ĳ������ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetEqosInfoCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetDynamicEpsQosInfoReq_PreProc
 ��������  : ��ѯEPS����������̬����Ԥ������
             (ID_MSG_TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetDynamicEpsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ������Ϣ��L4A */
    TAF_APS_SndL4aSetCgeqosrdpReq(pstPsMsg->aucContent);

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));
    /* ����L4A��Ϣ�ظ�������ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* �����Ϣ���ȴ����� */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF,
                                     (VOS_UINT32 *)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}

/* Add by w00199382 for V7����ͬ��, 2012-04-07, Begin   */

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetLteCsInfoReq_PreProc
 ��������  :
             (ID_MSG_TAF_PS_GET_LTE_CS_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��24��
    ��    ��   : h00135900
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetLteCsInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_PS_MSG_STRU                 *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

    /* ������Ϣ��L4A */
    TAF_APS_SndL4aGetLteCsReq(pstPsMsg->aucContent);

    /* ����L4A��Ϣ�ظ�������ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_GET_LTE_CS_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* �����Ϣ���ȴ����� */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_LTE_CS_CNF,
                                     (VOS_UINT32*)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_LTECS_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvL4aGetLteCsCnf_PreProc
 ��������  :
             (ID_L4A_APS_GET_LTE_CS_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��24��
    ��    ��   : h00135900
    �޸�����   : �����ɺ���
  2.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ���ӻ�������л�ȡ��Ϣ

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aGetLteCsCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_GET_LTE_CS_CNF_STRU        *pstPsMsg = VOS_NULL_PTR;
    TAF_PS_LTECS_CNF_STRU              *pstApsAtLteCsInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg = (APS_L4A_GET_LTE_CS_CNF_STRU*)pstMsg;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_GET_LTE_CS_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_GET_LTE_CS_CNF, ulPara);

        /* ����AT������ */
        pstApsAtLteCsInfo =  (TAF_PS_LTECS_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_PS_LTECS_CNF_STRU));

        if ( VOS_NULL_PTR == pstApsAtLteCsInfo )
        {
            /* ϵͳ�쳣��ӡ, ֱ�ӷ��� */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aGetLteCsCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        PS_MEM_SET(pstApsAtLteCsInfo, 0x00,  sizeof( TAF_PS_LTECS_CNF_STRU));

        /* L4A�������ת�� */
        pstApsAtLteCsInfo->enCause = TAF_APS_TransL4aErrorCode(pstPsMsg->ulErrorCode);

        /* �ӻ�������л�ȡ��Ϣ */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstApsAtLteCsInfo->stCtrl,
                                                              TI_TAF_APS_WAIT_GET_LTE_CS_CNF,
                                                              ulPara))
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aGetLteCsCnf_PreProc: Get message info failed!");

            /* �ͷ��ڴ� */
            PS_MEM_FREE(WUEPS_PID_TAF, pstApsAtLteCsInfo);

            return VOS_TRUE;
        }

        if(pstApsAtLteCsInfo->enCause == TAF_PS_CAUSE_SUCCESS )
        {
            pstApsAtLteCsInfo->stLteCs.ucSG     = pstPsMsg->ucSmsOverSGs;
            pstApsAtLteCsInfo->stLteCs.ucIMS    = pstPsMsg->ucSmsOverIMS;
            pstApsAtLteCsInfo->stLteCs.ucCSFB   = pstPsMsg->ucCSFB;
            pstApsAtLteCsInfo->stLteCs.ucVCC    = pstPsMsg->ucSrVcc;
            pstApsAtLteCsInfo->stLteCs.ucVoLGA  = pstPsMsg->ucVoLGA;
        }

        /* ����Ϣ���� */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_LTECS_INFO_CNF,
                         pstApsAtLteCsInfo,
                         sizeof(TAF_PS_LTECS_CNF_STRU));

        /* �ͷ��ڴ� */
        PS_MEM_FREE(WUEPS_PID_TAF, pstApsAtLteCsInfo);

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_LTE_CS_CNF, ulPara);

    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetCemodeInfoReq_PreProc
 ��������  :
             (ID_MSG_TAF_PS_GET_CEMODE_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2012��03��20��
    ��    ��   : w00182550
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetCemodeInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

    /* ������Ϣ��L4A */
    TAF_APS_SndL4aGetCemodeReq(pstPsMsg->aucContent);

    /* ����L4A��Ϣ�ظ�������ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_GET_CEMODE_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* �����Ϣ���ȴ����� */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_CEMODE_CNF,
                                     (VOS_UINT32*)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_CEMODE_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvL4aGetCemodeCnf_PreProc
 ��������  :
             (ID_L4A_APS_GET_CEMODE_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��03��20��
    ��    ��   : w00182550
    �޸�����   : �����ɺ���
  2.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ���ӻ�������л�ȡ��Ϣ
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aGetCemodeCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_GET_CEMODE_CNF_STRU        *pstPsMsg;
    TAF_PS_CEMODE_CNF_STRU             *pstApsAtCemodeInfo = NULL;
    VOS_UINT32                          i;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (APS_L4A_GET_CEMODE_CNF_STRU*)pstMsg;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_GET_CEMODE_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_GET_CEMODE_CNF, ulPara);

        /* ����AT������ */
        pstApsAtCemodeInfo =  (TAF_PS_CEMODE_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_PS_CEMODE_CNF_STRU));

        if ( VOS_NULL_PTR == pstApsAtCemodeInfo )
        {
            /* ϵͳ�쳣��ӡ, ֱ�ӷ��� */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aGetCemodeCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        PS_MEM_SET(pstApsAtCemodeInfo, 0x00,  sizeof( TAF_PS_CEMODE_CNF_STRU));

        /* L4A�������ת�� */
        pstApsAtCemodeInfo->enCause = TAF_APS_TransL4aErrorCode(pstPsMsg->ulErrorCode);;

        /* �ӻ�������л�ȡ��Ϣ */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstApsAtCemodeInfo->stCtrl,
                                                              TI_TAF_APS_WAIT_GET_CEMODE_CNF,
                                                              ulPara))
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aGetCemodeCnf_PreProc: Get message info failed!");

            /* �ͷ��ڴ� */
            PS_MEM_FREE(WUEPS_PID_TAF, pstApsAtCemodeInfo);

            return VOS_TRUE;
        }

        if (pstApsAtCemodeInfo->enCause == TAF_PS_CAUSE_SUCCESS )
        {
            pstApsAtCemodeInfo->stCemode.enCurrentUeMode    = pstPsMsg->ulCurrentUeMode;
            pstApsAtCemodeInfo->stCemode.ulSupportModeCnt   = pstPsMsg->ulSupportModeCnt;

            for (i = 0; i < 4; i++)
            {
                pstApsAtCemodeInfo->stCemode.aenSupportModeList[i] = pstPsMsg->aulSupportModeList[i];
            }
        }

            /* ����Ϣ����AT */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CEMODE_INFO_CNF,
                         pstApsAtCemodeInfo,
                         sizeof( TAF_PS_CEMODE_CNF_STRU));

        /* �ͷ��ڴ� */
        PS_MEM_FREE(WUEPS_PID_TAF, pstApsAtCemodeInfo);

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_CEMODE_CNF, ulPara);

    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdprofInfoReq_PreProc
 ��������  : ����APN, �û����������Ȩ��ϢԤ������
             (ID_MSG_TAF_PS_SET_PDPROFMOD_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��12��
    ��    ��   : x00126983
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdprofInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));
    /* ������Ϣ��L4A */
    TAF_APS_SndL4aSetPdprofReq(pstPsMsg->aucContent);

    /* ����L4A��Ϣ�ظ�������ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_PDPROF_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* �����Ϣ���ȴ����� */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_PDPROF_CNF,
                                     (VOS_UINT32*)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_SET_PROFILE_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvL4aSetPdprofInfoCnf_PreProc
 ��������  : CNF��ϢԤ������
             (ID_L4A_APS_SET_PDPROFMOD_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��03��15��
    ��    ��   : x00126983
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetPdprofInfoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_PDPROFMOD_CNF_STRU     *pstPsMsg;
    TAF_CTRL_STRU                       stCtrl = {0};
    VOS_UINT32                          ulErrCode;
    TAF_APS_CMD_BUFFER_STRU            *pstMsgInfo;
    TAF_PS_SET_PROFILE_INFO_REQ_STRU   *pstSetPdprofInfoReq;
    VOS_UINT32                          ulPara;

    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
    /* ��ʼ����Ϣ */
    pstPsMsg                = (APS_L4A_SET_PDPROFMOD_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetPdprofInfoReq     = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_PDPROF_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_PDPROF_CNF, ulPara);

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* �ӻ�������л�ȡ��Ϣ */
        pstMsgInfo  = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_PDPROF_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetPdprofInfoCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* ��Ϣ��ȡ�ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        pstSetPdprofInfoReq = (TAF_PS_SET_PROFILE_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;

        stCtrl = pstSetPdprofInfoReq->stCtrl;

        /* ���L4Aȫ�ֱ������³ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* ����Primary PDP�����ĺ�AUTHDATA����(NDIS)  */
            Aps_DefPsPdprofmod(pstSetPdprofInfoReq->stCtrl.usClientId,
                               pstSetPdprofInfoReq->stCtrl.ucOpId,
                               &(pstSetPdprofInfoReq->stPdpProfInfo),
                               &ulErrCode);
        }

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_PDPROF_CNF, ulPara);

        /* ����AT������ */
        TAF_APS_SndSetPdprofInfoCnf(&stCtrl, ulErrCode);
    }
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

    return VOS_TRUE;
}

/* Add by w00199382 for V7����ͬ��, 2012-04-07, End   */

#endif

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetAuthDataInfoReq_PreProc
 ��������  : ��ѯ�û����������Ȩ��ϢԤ������
             (ID_MSG_TAF_PS_GET_AUTHDATA_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetAuthDataInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvGetAuthDataInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetUmtsQosInfoReq_PreProc
 ��������  : ��ѯPDP�����ĵ�Qos������Ԥ������
             (ID_MSG_TAF_PS_GET_UMTS_QOS_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetUmtsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvGetUmtsQosInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetUmtsQosMinInfoReq_PreProc
 ��������  : ��ѯPDP�����ĵ���С�ɽ��ܷ�������Ԥ������
             (ID_MSG_TAF_PS_GET_UMTS_QOS_MIN_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetUmtsQosMinInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvGetUmtsQosMinInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetDynamicUmtsQosInfoReq_PreProc
 ��������  : ��ѯPDP�����ļ���󾭹�������Э�̺��ʵ��ʹ�õ�QoSԤ������
             (ID_MSG_TAF_PS_GET_DYNAMIC_UMTS_QOS_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetDynamicUmtsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvGetDynamicUmtsQosInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetPdpDnsInfoReq_PreProc
 ��������  : ��ѯPDP������ʹ�õ�DNS��ϢԤ������
             (ID_MSG_TAF_PS_GET_PDP_DNS_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetPdpDnsInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    (VOS_VOID)MN_APS_RcvGetPdpDnsInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPrimPdpCtxInfoReq_PreProc
 ��������  : ������PDP������Ԥ������
             (ID_MSG_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��26��
    ��    ��   : m00217266
    �޸�����   : DSDA C����Ŀ�ӿ��޸�(���ϵͳ�����ж�)
  3.��    ��   : 2014��02��14��
    ��    ��   : m00217266
    �޸�����   : L-C��������Ŀ(���������Ч���ж�)
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPrimPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                             *pstPsMsg;
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU   *pstSetPdpCtxInfoReq;
#if ( FEATURE_ON == FEATURE_LTE )
    VOS_UINT32                          ulPara;
#endif

    /* ��ʼ����Ϣ */
    pstPsMsg            = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpCtxInfoReq = (TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU *)pstPsMsg->aucContent;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* Added by m00217266 for L-C��������Ŀ, 2014-1-24, begin */
    /* L-C������ģʽ����������Ϣ��Ч�����ж� */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstSetPdpCtxInfoReq->stCtrl)))
    {
        TAF_APS_SndSetPrimPdpCtxInfoCnf(&(pstSetPdpCtxInfoReq->stCtrl), TAF_PARA_UNSPECIFIED_ERROR);
        return VOS_TRUE;
    }
    /* Added by m00217266 for L-C��������Ŀ, 2014-1-24, end */
#endif
#if ( FEATURE_ON == FEATURE_LTE )
    /* ����LTE�����ֱ�ִ�� */
    /* ĿǰESM��֧��PPP���͵Ĳ��� */
    if ((VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
     && (TAF_PDP_PPP != pstSetPdpCtxInfoReq->stPdpContextInfo.enPdpType))
    {
        /* ������Ϣ��L4A */
        TAF_APS_SndL4aSetCgdcontReq(pstSetPdpCtxInfoReq);

        ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstSetPdpCtxInfoReq),
                                               TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstSetPdpCtxInfoReq));

        /* ����L4A��Ϣ�ظ�������ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGDCONT_CNF,
                           TI_TAF_APS_WAIT_L4A_CNF_LEN,
                           ulPara);

        /* �����Ϣ���ȴ����� */
        TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDCONT_CNF,
                                         (VOS_UINT32*)pstSetPdpCtxInfoReq,
                                         sizeof(TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU),
                                         ulPara);

       return VOS_TRUE;
    }

#endif

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvSetPrimPdpCtxInfoReq(pstSetPdpCtxInfoReq);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetSecPdpCtxInfoReq_PreProc
 ��������  : ���ô�PDP������Ԥ������
             (ID_MSG_TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��26��
    ��    ��   : m00217266
    �޸�����   : DSDA C����Ŀ�ӿ��޸�(���ϵͳ�����ж�)
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetSecPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
#if ( FEATURE_ON == FEATURE_LTE )
    VOS_UINT32                          ulPara;
#endif

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

#if ( FEATURE_ON == FEATURE_LTE )
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        /* ������Ϣ��L4A */
        TAF_APS_SndL4aSetCgdscontReq(pstPsMsg->aucContent);

        ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                               TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));
        /* ����L4A��Ϣ�ظ�������ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF,
                           TI_TAF_APS_WAIT_L4A_CNF_LEN,
                           ulPara);

        /* �����Ϣ���ȴ����� */
        TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF,
                                         (VOS_UINT32*)pstPsMsg->aucContent,
                                         sizeof(TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU),
                                         ulPara);

	    return VOS_TRUE;
    }
#endif

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvSetSecPdpCtxInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetTftInfoReq_PreProc
 ��������  : ����TFT����Ԥ������
             (ID_MSG_TAF_PS_SET_TFT_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��26��
    ��    ��   : m00217266
    �޸�����   : DSDA C����Ŀ�ӿ��޸�(���ϵͳ�����ж�)
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetTftInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
#if ( FEATURE_ON == FEATURE_LTE )
    VOS_UINT32                          ulPara;
#endif

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;
#if ( FEATURE_ON == FEATURE_LTE )
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        /* ������Ϣ��L4A */
        TAF_APS_SndL4aSetCgtftReq(pstPsMsg->aucContent);

        ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                               TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

        /* ����L4A��Ϣ�ظ�������ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGTFT_CNF,
                           TI_TAF_APS_WAIT_L4A_CNF_LEN,
                           ulPara);

        /* �����Ϣ���ȴ����� */
        TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFT_CNF,
                                         (VOS_UINT32*)pstPsMsg->aucContent,
                                         sizeof(TAF_PS_SET_TFT_INFO_REQ_STRU),
                                         ulPara);

        return VOS_TRUE;
    }

#endif

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvSetTftInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetAnsModeInfoReq_PreProc
 ��������  : PS����Զ�Ӧ��״̬����Ԥ������
             (ID_MSG_TAF_PS_SET_ANSWER_MODE_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��26��
    ��    ��   : m00217266
    �޸�����   : DSDA C����Ŀ�ӿ��޸�(���ϵͳ�����ж�)
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetAnsModeInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
#if ( FEATURE_ON == FEATURE_LTE )
    VOS_UINT32                          ulPara;
#endif

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

#if ( FEATURE_ON == FEATURE_LTE )
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        /* ������Ϣ��L4A */
        TAF_APS_SndL4aSetCgautoReq(pstPsMsg->aucContent);

        ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                               TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));
        /* ����L4A��Ϣ�ظ�������ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGAUTO_CNF,
                           TI_TAF_APS_WAIT_L4A_CNF_LEN,
                           ulPara);

        /* �����Ϣ���ȴ����� */
        TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGAUTO_CNF,
                                         (VOS_UINT32*)pstPsMsg->aucContent,
                                         sizeof(TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU),
                                         ulPara);

        return VOS_TRUE;
    }
#endif

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvSetAnsModeInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetAuthDataInfoReq_PreProc
 ��������  : �����û����������Ȩ��ϢԤ������
             (ID_MSG_TAF_PS_SET_AUTHDATA_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��26��
    ��    ��   : m00217266
    �޸�����   : DSDA C����Ŀ�ӿ��޸�(���ϵͳ�����ж�)
  3.��    ��   : 2014��02��14��
    ��    ��   : m00217266
    �޸�����   : L-C��������Ŀ(���������Ч���ж�)
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetAuthDataInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                     *pstPsMsg;
    TAF_PS_SET_AUTHDATA_INFO_REQ_STRU   *pstAuthdata;
#if ( FEATURE_ON == FEATURE_LTE )
    VOS_UINT32                          ulPara;
#endif

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstAuthdata     = (TAF_PS_SET_AUTHDATA_INFO_REQ_STRU *)pstPsMsg->aucContent;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* Added by m00217266 for L-C��������Ŀ, 2014-1-24, begin */
    /* L-C������ģʽ����������Ϣ��Ч�����ж� */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstAuthdata->stCtrl)))
    {
        (VOS_VOID)TAF_APS_SndSetAuthDataInfoCnf(&(pstAuthdata->stCtrl), TAF_PARA_UNSPECIFIED_ERROR);
        return VOS_TRUE;
    }
    /* Added by m00217266 for L-C��������Ŀ, 2014-1-24, end */
#endif

#if ( FEATURE_ON == FEATURE_LTE )
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        /* ������Ϣ��L4A */
        TAF_APS_SndL4aSetAuthdataReq(pstAuthdata);

        ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstAuthdata),
                                               TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstAuthdata));

        /* ����L4A��Ϣ�ظ�������ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF,
                           TI_TAF_APS_WAIT_L4A_CNF_LEN,
                           ulPara);

        /* �����Ϣ���ȴ����� */
        TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF,
                                         (VOS_UINT32*)pstAuthdata,
                                         sizeof(TAF_PS_SET_AUTHDATA_INFO_REQ_STRU),
                                         ulPara);

        return VOS_TRUE;
    }
#endif

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvSetAuthDataInfoReq(pstAuthdata);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetUmtsQosInfoReq_PreProc
 ��������  : ����PDP�����ĵ�Qos������Ԥ������
             (ID_MSG_TAF_PS_SET_UMTS_QOS_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��02��14��
    ��    ��   : m00217266
    �޸�����   : L-C��������Ŀ(���������Ч���ж�)
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetUmtsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                     *pstPsMsg;
    TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU   *pstSetQosReq;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetQosReq    = (TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU *)pstPsMsg->aucContent;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* Added by m00217266 for L-C��������Ŀ, 2014-1-24, begin */
    /* L-C������ģʽ����������Ϣ��Ч�����ж� */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstSetQosReq->stCtrl)))
    {
        TAF_APS_SndSetUmtsQosInfoCnf(&(pstSetQosReq->stCtrl), TAF_PARA_UNSPECIFIED_ERROR);
        return VOS_TRUE;
    }
    /* Added by m00217266 for L-C��������Ŀ, 2014-1-24, end */
#endif

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvSetUmtsQosInfoReq(pstSetQosReq);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetUmtsQosMinInfoReq_PreProc
 ��������  : ����PDP�����ĵ���С�ɽ��ܷ�������Ԥ������
             (ID_MSG_TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��02��14��
    ��    ��   : m00217266
    �޸�����   : L-C��������Ŀ(���������Ч���ж�)
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetUmtsQosMinInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                         *pstPsMsg;
    TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU   *pstSetQosMinReq;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetQosMinReq = (TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU *)pstPsMsg->aucContent;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* Added by m00217266 for L-C��������Ŀ, 2014-1-24, begin */
    /* L-C������ģʽ����������Ϣ��Ч�����ж� */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstSetQosMinReq->stCtrl)))
    {
        TAF_APS_SndSetUmtsQosMinInfoCnf(&(pstSetQosMinReq->stCtrl), TAF_PARA_UNSPECIFIED_ERROR);
        return VOS_TRUE;
    }
    /* Added by m00217266 for L-C��������Ŀ, 2014-1-24, end */
#endif

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvSetUmtsQosMinInfoReq(pstSetQosMinReq);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpDnsInfoReq_PreProc
 ��������  : ����PDP������ʹ�õ�DNS��ϢԤ������
             (ID_MSG_TAF_PS_SET_PDP_DNS_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpDnsInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    (VOS_VOID)MN_APS_RcvSetPdpDnsInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtTrigGprsDataReq_PreProc
 ��������  : ��ϢԤ������
             (ID_MSG_TAF_PS_TRIG_GPRS_DATA_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtTrigGprsDataReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_TRIG_GPRS_DATA_REQ_STRU     *pstTrigReq = VOS_NULL_PTR;

    pstTrigReq  = (TAF_PS_TRIG_GPRS_DATA_REQ_STRU*)TAF_PS_GET_MSG_CONTENT(pstMsg);

    TAF_APS_GprsDataReq(pstTrigReq->stGprsDataInfo.ucMode,
                        pstTrigReq->stGprsDataInfo.ucNsapi,
                        pstTrigReq->stGprsDataInfo.ulLength,
                        pstTrigReq->stGprsDataInfo.ucTimes,
                        pstTrigReq->stGprsDataInfo.ulMillisecond);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtConfigNbnsFunctionReq_PreProc
 ��������  : ��ϢԤ������
             (ID_MSG_TAF_PS_CONFIG_NBNS_FUNCTION_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtConfigNbnsFunctionReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvConfigNbnsFunctionReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvFindCidForDialReq_PreProc
 ��������  : ��ѯCID����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtFindCidForDialReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU  *pCnf;
    VOS_UINT8                                 ucCid;

    pCnf = (TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                                   sizeof(TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pCnf)
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:alloc msg failed.");
        return VOS_TRUE;
    }

    /* ���ҿ����ڲ��ŵ�CID */
    ucCid = TAF_APS_FindCidForDial(WUEPS_PID_AT);
    if ( TAF_INVALID_CID == ucCid )
    {
        pCnf->ulRet       = VOS_ERR;
    }

    pCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pCnf->enMsgId                       = ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF;
    pCnf->ulRet                         = VOS_OK;
    pCnf->ucCid                         = ucCid;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pCnf))
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:send msg failed.");

        return VOS_TRUE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetCidParaReq_PreProc
 ��������  : ��ȡCID�Ĳ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetCidParaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAFAGENT_APS_GET_CID_PARA_CNF_STRU         *pCnf;
    TAFAGENT_APS_GET_CID_PARA_REQ_STRU         *pMsgReq;
    VOS_UINT32                                  ulResult;

    pCnf = (TAFAGENT_APS_GET_CID_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                              sizeof(TAFAGENT_APS_GET_CID_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pCnf)
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:alloc msg failed.");
        return VOS_TRUE;
    }

    pMsgReq                             = (TAFAGENT_APS_GET_CID_PARA_REQ_STRU*)pstMsg;

    ulResult                            = MN_APS_GetPdpCidPara(&(pCnf->stCidInfo),pMsgReq->ucCid);

    pCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pCnf->enMsgId                       = ID_TAFAGENT_APS_GET_CID_PARA_CNF;
    pCnf->ulRet                         = (VOS_UINT8)ulResult;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pCnf))
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:send msg failed.");

        return VOS_TRUE;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_SetCidParaReq_PreProc
 ��������  : ����CID�Ĳ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetCidParaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAFAGENT_APS_SET_CID_PARA_REQ_STRU                         *pMsgReq;
    TAFAGENT_APS_SET_CID_PARA_CNF_STRU                         *pCnf;
    VOS_UINT32                                                  ulResult;

    pCnf = (TAFAGENT_APS_SET_CID_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                sizeof(TAFAGENT_APS_SET_CID_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pCnf)
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:alloc msg failed.");
        return VOS_TRUE;
    }

    pMsgReq                  = (TAFAGENT_APS_SET_CID_PARA_REQ_STRU*)(pstMsg);
    ulResult                 = MN_APS_SetPdpCidPara((VOS_UINT16)pMsgReq->ulClientID,&(pMsgReq->stPdpPrimContextExt));

    pCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pCnf->enMsgId                       = ID_TAFAGENT_APS_SET_CID_PARA_CNF;
    pCnf->ulRet                         = (VOS_UINT8)ulResult;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pCnf))
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:send msg failed.");

        return VOS_TRUE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetCidQosParaReq_PreProc
 ��������  : ��ȡCID��QOS����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��29��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��01��20��
    ��    ��   : z00301431
    �޸�����   : DTS2015012000798, ��Ϣ�����δ��ʼ������min qos���ô���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetCidQosParaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU         *pCnf;
    TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU         *pMsgReq;
    VOS_UINT32                                      ulResult;

    pCnf = (TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                              sizeof(TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pCnf)
    {
        APS_ERR_LOG("TAF_APS_GetCidQosParaReq_PreProc:alloc msg failed.");
        return VOS_TRUE;
    }

    PS_MEM_SET((VOS_CHAR*)pCnf + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pMsgReq                             = (TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU*)pstMsg;

    ulResult                            = TAF_APS_GetPdpCidQosPara(&(pCnf->stQosPara), pMsgReq->ucCid);

    pCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pCnf->enMsgId                       = ID_TAFAGENT_APS_GET_CID_QOS_PARA_CNF;
    pCnf->ulRet                         = (VOS_UINT8)ulResult;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pCnf))
    {
        APS_ERR_LOG("TAF_APS_RcvAtGetCidQosParaReq_PreProc:send msg failed.");

        return VOS_TRUE;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetCidQosParaReq_PreProc
 ��������  : ����CID��Qos����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��29��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetCidQosParaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU                         *pMsgReq;
    TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU                         *pCnf;
    VOS_UINT32                                                      ulResult;

    pCnf = (TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                sizeof(TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pCnf)
    {
        APS_ERR_LOG("TAF_APS_RcvAtSetCidQosParaReq_PreProc:alloc msg failed.");
        return VOS_TRUE;
    }

    pMsgReq                  = (TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU*)(pstMsg);

    ulResult                 = TAF_APS_SetPdpCidQosPara(&(pMsgReq->stQosPara));

    pCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pCnf->enMsgId                       = ID_TAFAGENT_APS_SET_CID_QOS_PARA_CNF;
    pCnf->ulRet                         = (VOS_UINT8)ulResult;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pCnf))
    {
        APS_ERR_LOG("TAF_APS_RcvAtSetCidQosParaReq_PreProc:send msg failed.");

        return VOS_TRUE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_PreProc
 ��������  : ����ȥ���������ĵ�ʱ����Ҫ����Ԥ�����ж���ǰ�Ƿ��ܽ���״̬��
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
  1.��    ��  : 2011��12��22��
    ��    ��  : h44270
    �޸�����  : �����ɺ���

  2.��    ��   : 2012��4��16��
    ��    ��   : A00165503
    �޸�����   : DTS2012040100697: �Զ�Ӧ��ģʽ��, ���ཨ����ESP����, �û���
                 ���޸ĺ�ȥ����

  3.��    ��   : 2012��11��13��
    ��    ��   : A00165503
    �޸�����   : DTS2012111205973: LTEĬ��ȱʡ����IP����IPv4v6, �û�����IP��
                 ��IPv4 only��IPv6 only, ȱʡ����IP���ͱ�������޸�Ϊ�û���
                 ��IP����

  4.��    ��   : 2014��02��14��
    ��    ��   : m00217266
    �޸�����   : L-C��������Ŀ(���������Ч���ж�)
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq;
    VOS_UINT8                           ucCidValue;
    VOS_UINT32                          ulBearerActivateFlg;
    VOS_UINT32                          ulRslt;

    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpStateReq                   = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* Added by m00217266 for L-C��������Ŀ, 2014-1-24, begin */
    /* L-C������ģʽ����������Ϣ��Ч�����ж� */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstSetPdpStateReq->stCtrl)))
    {
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl), TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }
    /* Added by m00217266 for L-C��������Ŀ, 2014-1-24, end */
#endif

    /* ���ü����� */
    ulBearerActivateFlg = (TAF_CGACT_ACT == pstSetPdpStateReq->stCidListStateInfo.ucState) ? VOS_TRUE : VOS_FALSE;

    /*
       ��ǰ�Ȳ�֧��һ���Լ�����PDP�ĳ�����һ�μ���һ��������ҵ�һ��Ҫ�����
       CID
    */
    ucCidValue = TAF_APS_GetCidValue(ulBearerActivateFlg, pstSetPdpStateReq->stCidListStateInfo.aucCid);

    /* ������ص�CIDΪ0����������ЧCID��ֱ�ӷ���ERROR */
    if (0 == ucCidValue)
    {
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
        return VOS_TRUE;
    }

    if (ulBearerActivateFlg == VOS_TRUE)
    {
        ulRslt = TAF_APS_ProcActivatePdpContext_PreProc(ucCidValue, pstSetPdpStateReq);
    }
    else
    {
        ulRslt = TAF_APS_ProcDeactivatePdpContext_PreProc(ucCidValue, pstSetPdpStateReq);
    }

    return ulRslt;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ProcActivatePdpContext_PreProc
 ��������  : Ԥ����״̬���д���PDP����
 �������  :    ucCidValue
                pstSetPdpStateReq
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��17��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��02��25��
    ��    ��   : Y00213812
    �޸�����   : DTS2014022504539:ֻ֧��IMSA�������˿ڹ���APN

  3.��    ��   : 2014��5��16��
    ��    ��   : A00165503
    �޸�����   : DTS2014050703206: ��������ƥ�䴦��
*****************************************************************************/
VOS_UINT32 TAF_APS_ProcActivatePdpContext_PreProc(
    VOS_UINT8                           ucCidValue,
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq
)
{
    TAF_APS_MATCH_PARAM_STRU            stMatchParam;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucPdpId;
    TAF_PH_MODE                         ucPhMode;

    PS_MEM_SET(&stMatchParam, 0x00, sizeof(TAF_APS_MATCH_PARAM_STRU));

    ucPhMode = MMA_GetCurrPhMode();

    /* ���ϵͳΪ����,��ֱ�ӷ���VOS_TRUE */
    if ( TAF_PH_MODE_FULL != ucPhMode )
    {
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                    TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }

    /* CID��Ӧ��������û�ж��壬��ֱ�ӷ���ERROR */
    if (VOS_FALSE == TAF_APS_GetTafCidInfoUsedFlg(ucCidValue))
    {
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
        return VOS_TRUE;
    }

    /* ����ƥ�������Ϣ */
    TAF_APS_GenMatchParamByCidInfo(TAF_APS_GetTafCidInfoAddr(ucCidValue),
                                   &stMatchParam);

#if (FEATURE_ON == FEATURE_LTE)
    /* �ҵ�Ĭ�ϳ��ص�����£�ֱ��ˢ��CID  */
    if (VOS_TRUE == TAF_APS_MatchCallWithAttachBearer(
                                &pstSetPdpStateReq->stCtrl,
                                &stMatchParam))
    {
        /* ����ˢ��CID����ͬʱˢ����ClientId��OP ID */
        ucPdpId = TAF_APS_GetPdpIdByDefaultCid();

        /* ���cid 0 ����Ϣ,��¼PDP ��Ϣ */
        TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                    ucCidValue,
                                    pstSetPdpStateReq->stCtrl.ulModuleId,
                                    pstSetPdpStateReq->stCtrl.usClientId,
                                    pstSetPdpStateReq->stCtrl.ucOpId);

        TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCidValue, TAF_APS_GetTafCidInfoPdpType(ucCidValue));

        /* ֪ͨESM��ǰ��Cidˢ�� */
        MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                SM_ESM_PDP_OPT_MODIFY);

        return VOS_FALSE;
    }
#endif

    /* ��ȡPdpId�������ȡ������˵����ǰ�Ǽ���һ���µ�CID */
    ucPdpId = TAF_APS_GetPdpIdByCid(ucCidValue);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* ��ͬAPN
           ����Ѽ�����ͬAPN��PDP�������ݣ�����PDPʵ��
           ����Ѽ�����ͬAPN��PDP���Ͳ�ͬ�����·���PDPʵ��
           δ����: ACTIVATING,MODIFING,DEACTIVATING
           ��������ԭ��ֵTAF_PS_CAUSE_SAME_APN_OPERATING

           ����ͬAPN��ִ��ԭ������
        */

        /* ���������һ���µ�PDP ID */
        if (VOS_TRUE == TAF_APS_MatchCallWithAllBearer(
                                    &pstSetPdpStateReq->stCtrl,
                                    &stMatchParam,
                                    &ucPdpId))
        {
            /* δ����: ACTIVATING,MODIFING,DEACTIVATING
               ��������ԭ��ֵTAF_PS_CAUSE_SAME_APN_OPERATING */
            if (TAF_APS_STA_ACTIVE != TAF_APS_GetPdpIdMainFsmState(ucPdpId))
            {
                TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                             TAF_PS_CAUSE_OPERATION_CONFLICT);
                return VOS_TRUE;
            }
            else
            {
                /* ��¼PDP��Ϣ */
                TAF_APS_AddPdpEntClientInfo(ucPdpId,
                                            ucCidValue,
                                            &(pstSetPdpStateReq->stCtrl));

                TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                             ucCidValue,
                                             TAF_APS_GetTafCidInfoPdpType(ucCidValue));
            }
        }
        else
        {
            /* ����TI(PdP Id) */
            if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&pstSetPdpStateReq->stCtrl,
                                                               ucCidValue,
                                                               &ucPdpId))
            {
                /* ���䲻��ʵ�壬��ֱ�ӷ���ERROR */
                TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                            TAF_PS_CAUSE_UNKNOWN);
                return VOS_TRUE;
            }
        }
    }
    else
    {
        if (TAF_APS_GetPdpEntClientId(ucPdpId, ucCidValue) != pstSetPdpStateReq->stCtrl.usClientId)
        {
            /* ClientId��ƥ��, ��ֱ�ӷ���ERROR */
            TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                        TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }
    }

    ulRslt = TAF_APS_RcvAtSetPdpContextStateReq_PdpActLimit_PreProc(pstSetPdpStateReq);

    return ulRslt;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ProcDeactivatePdpContext_PreProc
 ��������  : Ԥ����״̬������PDPȥ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��17��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��12��17��
    ��    ��   : Y00213812
    �޸�����   : ���Ӷ��û�����APN�Ĵ���
*****************************************************************************/
VOS_UINT32 TAF_APS_ProcDeactivatePdpContext_PreProc(
    VOS_UINT8                           ucCidValue,
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_BITCID_INFO_STRU            stCid;

    PS_MEM_SET(&stCid, 0, sizeof(TAF_APS_BITCID_INFO_STRU));

    /* ��ȡPdpId�������ȡ������˵����ǰ��ȥ����һ���µ�CID */
    ucPdpId = TAF_APS_GetPdpIdByCid(ucCidValue);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /*
           ȥ��������������ȥ����һ���µ�CID,˵����ǰ��Ӧ��CID��û�м���
           ���߳��Լ��ֱ�ӷ���OK
        */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                    TAF_PS_CAUSE_SUCCESS);

        /* û���ҵ�ƥ���PDP, ���PDPû�м���, �ϱ�ȥ����ɹ��¼� */
        TAF_APS_SndCidInactiveEvt(&(pstSetPdpStateReq->stCtrl),
                                  ucCidValue);

        return VOS_TRUE;
    }
    else
    {
        if (TAF_APS_INVALID_CLIENTID == TAF_APS_GetPdpEntClientId(ucPdpId, ucCidValue))
        {
            TAF_APS_SetPdpEntClientId(ucPdpId, ucCidValue, pstSetPdpStateReq->stCtrl.usClientId);
        }
        else if (TAF_APS_GetPdpEntClientId(ucPdpId, ucCidValue) != pstSetPdpStateReq->stCtrl.usClientId)
        {
            /* ClientId��ƥ��, ��ֱ�ӷ���ERROR */
            TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                         TAF_PS_CAUSE_UNKNOWN);

            return VOS_TRUE;
        }
        else
        {
            /* ���PDPʵ�����Ƿ���ڶ��cid */
            TAF_APS_GetPdpEntBitCidInfo(ucPdpId, &stCid);

            if (stCid.ulNum > 1)
            {
                /* ���ظ�cidȥ����ɹ� */
                TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                             TAF_PS_CAUSE_SUCCESS);

                TAF_APS_SndPdpDeActivateCnf(ucPdpId, ucCidValue);

                /* ���PDPʵ���и�CID��Ϣ */
                TAF_APS_RmvPdpEntClientInfo(ucPdpId, ucCidValue, &stCid);

                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallModifyReq_PreProc
 ��������  : �յ�modify��Ϣ��ʱ����Ҫ����Ԥ�����ж���ǰ�Ƿ��ܽ���״̬��
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��22��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��03��05��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ��:DTS2012022405416��G������פ��������PDP MOD REQ,
                 PDP�޸������ϵͳ��W�£�PS��BAR��AT����Ӧ

  3.��    ��   : 2012��4��16��
    ��    ��   : A00165503
    �޸�����   : DTS2012040100697: �Զ�Ӧ��ģʽ��, ���ཨ����ESP����, �û���
                 ���޸ĺ�ȥ����
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCidValue;
    VOS_UINT32                          ulBearerActivateFlg;
    TAF_APS_BITCID_INFO_STRU                     stCid;

    PS_MEM_SET(&stCid, 0, sizeof(TAF_APS_BITCID_INFO_STRU));

    /* ��ǰ�Ȳ�֧��һ����Modify���PDP�ĳ�����һ��Modifyһ�� */
    ulBearerActivateFlg                 = VOS_FALSE;
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    ucCidValue = TAF_APS_GetCidValue(ulBearerActivateFlg, pstCallModifyReq->stCidListInfo.aucCid);

    /* ������ص�CIDΪ0����������ЧCID��ֱ�ӷ���ERROR */
    if ( 0 == ucCidValue )
    {
        /* �ϱ�ERROR */
        TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                                TAF_PS_CAUSE_CID_INVALID);
        return VOS_TRUE;

    }

    /* ��ȡPdpId�������ȡ������˵����ǰû�п����޸ĵ�PDP ID */
    ucPdpId = TAF_APS_GetPdpIdByCid(ucCidValue);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* ֱ�ӷ���ERROR */
        TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                                TAF_PS_CAUSE_CID_INVALID);
        return VOS_TRUE;
    }

    /* ���PDPʵ�����Ƿ���ڶ��cid */
    TAF_APS_GetPdpEntBitCidInfo(ucPdpId, &stCid);
    if (stCid.ulNum > 1)
    {
        /* ����APN����ʱ���������û�����MODIFY */
        TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                                 TAF_PS_CAUSE_OPERATION_CONFLICT);
        return VOS_TRUE;
    }

    TAF_APS_SetPdpEntModDialInfo(ucPdpId, &(pstCallModifyReq->stCtrl));

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallOrigReq_PreProc
 ��������  : �յ�������Ϣ��ʱ����Ҫ����Ԥ�����ж���ǰ�Ƿ��ܽ���״̬��
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��22��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��11��13��
    ��    ��   : A00165503
    �޸�����   : DTS2012111205973: LTEĬ��ȱʡ����IP����IPv4v6, �û�����IP��
                 ��IPv4 only��IPv6 only, ȱʡ����IP���ͱ�������޸�Ϊ�û���
                 ��IP����

  3.��    ��   : 2014��02��25��
    ��    ��   : Y00213812
    �޸�����   : DTS2014022504539:ֻ֧��IMSA�������˿ڹ���APN

  4.��    ��   : 2014��02��14��
    ��    ��   : m00217266
    �޸�����   : L-C��������Ŀ(���������Ч���ж�)

  5.��    ��   : 2014��5��16��
    ��    ��   : A00165503
    �޸�����   : DTS2014050703206: ��������ƥ�䴦��
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;
    TAF_APS_MATCH_PARAM_STRU            stMatchParam;
    VOS_UINT8                           ucPdpId;
    TAF_PH_MODE                         ucPhMode;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_SDC_1X_SYS_INFO_STRU           *pstSdc1xSysInfo = VOS_NULL_PTR;
#endif

    PS_MEM_SET(&stMatchParam, 0x00, sizeof(TAF_APS_MATCH_PARAM_STRU));

    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPhMode                            = MMA_GetCurrPhMode();
    ucPdpId                             = TAF_APS_INVALID_PDPID;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* Added by m00217266 for L-C��������Ŀ, 2014-1-24, begin */
    /* L-C������ģʽ����������Ϣ��Ч�����ж� */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstCallOrigReq->stCtrl)))
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                      pstCallOrigReq->stDialParaInfo.ucCid,
                      TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }
    /* Added by m00217266 for L-C��������Ŀ, 2014-1-24, end */
#endif

    /* ���ϵͳΪ��������ֱ�ӷ���VOS_TRUE */
    if (TAF_PH_MODE_FULL != ucPhMode)
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                              pstCallOrigReq->stDialParaInfo.ucCid,
                              TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    pstSdc1xSysInfo = TAF_SDC_Get1xSysInfo();

    /* CallBack״̬�����ܽ��в��� */
    if (VOS_TRUE == pstSdc1xSysInfo->ucIsEmcCallExistFlg)
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                              pstCallOrigReq->stDialParaInfo.ucCid,
                              TAF_PS_CAUSE_UNKNOWN);

        return VOS_TRUE;
    }
#endif

    /* ����ƥ�������Ϣ */
    TAF_APS_GenMatchParamByDailInfo(&pstCallOrigReq->stDialParaInfo,
                                    &stMatchParam);

    /* �ҵ�Ĭ�ϳ��ص�����£�ֱ��ˢ��CID  */
    if (VOS_TRUE == TAF_APS_MatchCallWithAttachBearer(
                                &pstCallOrigReq->stCtrl,
                                &stMatchParam))
    {
        /* ����ˢ��CID����ͬʱˢ����ClientId��OP ID */
        ucPdpId = TAF_APS_GetPdpIdByDefaultCid();

        /* ���CID 0 ����Ϣ,��¼PDP ��Ϣ */
        TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                    pstCallOrigReq->stDialParaInfo.ucCid,
                                    pstCallOrigReq->stCtrl.ulModuleId,
                                    pstCallOrigReq->stCtrl.usClientId,
                                    pstCallOrigReq->stCtrl.ucOpId);

        TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                     pstCallOrigReq->stDialParaInfo.ucCid,
                                     pstCallOrigReq->stDialParaInfo.enPdpType);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

        /* ֪ͨEHSM��ǰ��Cidˢ�� */
        TAF_APS_SndEhsmPdnCtxInfoNotify(ucPdpId, EHSM_APS_PDN_OPTION_MODIFIED);

#endif

#if (FEATURE_ON == FEATURE_LTE)
        /* ֪ͨESM��ǰ��Cidˢ�� */
        MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                SM_ESM_PDP_OPT_MODIFY);
#endif

        return VOS_FALSE;
    }

    /* ��ȡPdpId�������ȡ������˵����ǰ�Ǽ������ȥ����һ���µ�CID */
    ucPdpId = TAF_APS_GetPdpIdByCid(pstCallOrigReq->stDialParaInfo.ucCid);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* ��ͬAPN
             ����Ѽ�����ͬAPN��PDP�������ݣ�����PDPʵ��
             ����Ѽ�����ͬAPN��PDP���Ͳ�ͬ�����·���PDPʵ��
             δ����: ACTIVATING,MODIFING,DEACTIVATING
             ��������ԭ��ֵTAF_PS_CAUSE_SAME_APN_OPERATING

           ����ͬAPN��ִ��ԭ������  */
        if (VOS_TRUE == TAF_APS_MatchCallWithAllBearer(
                                    &pstCallOrigReq->stCtrl,
                                    &stMatchParam,
                                    &ucPdpId))
        {
            /* δ����: ACTIVATING,MODIFING,DEACTIVATING
               ��������ԭ��ֵTAF_PS_CAUSE_SAME_APN_OPERATING */
            if (TAF_APS_STA_ACTIVE != TAF_APS_GetPdpIdMainFsmState(ucPdpId))
            {
                TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                                       pstCallOrigReq->stDialParaInfo.ucCid,
                                       TAF_PS_CAUSE_OPERATION_CONFLICT);
                return VOS_TRUE;
            }
            else
            {
                /* ��¼PDP��Ϣ */
                TAF_APS_AddPdpEntClientInfo(ucPdpId,
                                            pstCallOrigReq->stDialParaInfo.ucCid,
                                            &(pstCallOrigReq->stCtrl));

                TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                             pstCallOrigReq->stDialParaInfo.ucCid,
                                             pstCallOrigReq->stDialParaInfo.enPdpType);
            }
        }
        else
        {
            /* ����ʵ�� */
            if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&pstCallOrigReq->stCtrl,
                                                               pstCallOrigReq->stDialParaInfo.ucCid,
                                                               &ucPdpId))
            {
                /* ���䲻��ʵ�壬��ֱ�ӷ���ERROR */
                TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                                      pstCallOrigReq->stDialParaInfo.ucCid,
                                      TAF_PS_CAUSE_UNKNOWN);
                return VOS_TRUE;
            }
        }
    }
    else
    {
        if (TAF_APS_GetPdpEntClientId(ucPdpId, pstCallOrigReq->stDialParaInfo.ucCid) != pstCallOrigReq->stCtrl.usClientId)
        {
            /* ClientId��ƥ��, ��ֱ�ӷ���ERROR */
            TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                                  pstCallOrigReq->stDialParaInfo.ucCid,
                                  TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }
    }

    if (VOS_TRUE == TAF_APS_IsPdpActLimit_PreProc())
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                              pstCallOrigReq->stDialParaInfo.ucCid,
                              TAF_PS_CAUSE_PDP_ACTIVATE_LIMIT);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_IsStaNwActivatingSubStaWaitAppAnswer
 ��������  : �жϵ�ǰ�������缤��ȴ�Ӧ�÷���Ӧ��״̬
 �������  : TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��7��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_IsStaNwActivatingSubStaWaitAppAnswer(
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq
)
{
    VOS_UINT8                           ucPdpId;

    /* ����CID��ȡPDP ID */
    ucPdpId = TAF_APS_GetPdpIdByCid(pstPppDialOrigReq->stPppDialParaInfo.ucCid);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* �����ȡ������˵������Ӧ�����缤�� */
        return VOS_FALSE;
    }

    /* �ҵ�PDP ID���ȡ��Ӧ��״̬��������������缤��ȴ��û�Ӧ��״̬��˵������Ӧ�����缤�� */
    if (TAF_APS_STA_NW_ACTIVATING != TAF_APS_GetPdpIdMainFsmState(ucPdpId))
    {
        return VOS_FALSE;
    }

    if (TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER != TAF_APS_GetPdpIdSubFsmState(ucPdpId))
    {
        return VOS_FALSE;
    }

    /* �ж϶˿��Ƿ�һ�� */
    if (pstPppDialOrigReq->stCtrl.usClientId != TAF_APS_GetPdpEntClientId(ucPdpId, pstPppDialOrigReq->stPppDialParaInfo.ucCid))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPppDialOrigReq_PreProc
 ��������  : �յ�PPP���ż�����Ϣ��ʱ����Ҫ����Ԥ�����ж���ǰ�Ƿ��ܽ���״̬��
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
  1.��    ��   : 2011��12��22��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��11��13��
    ��    ��   : A00165503
    �޸�����   : DTS2012111205973: LTEĬ��ȱʡ����IP����IPv4v6, �û�����IP��
                 ��IPv4 only��IPv6 only, ȱʡ����IP���ͱ�������޸�Ϊ�û���
                 ��IP����
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPppDialOrigReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg = VOS_NULL_PTR;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;
    TAF_PH_MODE                         ucPhMode;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulErrCode;
#endif
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_SDC_1X_SYS_INFO_STRU           *pstSdc1xSysInfo = VOS_NULL_PTR;
#endif

    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPhMode                            = MMA_GetCurrPhMode();

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    pstSdc1xSysInfo = TAF_SDC_Get1xSysInfo();

    /* CallBack״̬�����ܽ��в��� */
    if (VOS_TRUE == pstSdc1xSysInfo->ucIsEmcCallExistFlg)
    {
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                TAF_PS_CAUSE_UNKNOWN);

        return VOS_TRUE;
    }
#endif

    /* �жϵ�ǰ�������缤��ȴ��û�Ӧ��״̬��ֱ�ӽ���״̬�� */
    if (VOS_TRUE == TAF_APS_IsStaNwActivatingSubStaWaitAppAnswer(pstPppDialOrigReq))
    {
        return VOS_FALSE;
    }

    /* ���ϵͳδ���������CID��Ӧ��������û�ж��壬��ֱ�ӷ���ERROR */
    if ( (TAF_PH_MODE_FULL != ucPhMode)
      || (VOS_FALSE == TAF_APS_GetTafCidInfoUsedFlg(pstPppDialOrigReq->stPppDialParaInfo.ucCid)) )
    {
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                 TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        ulErrCode = TAF_ERR_NO_ERROR;

        ulResult = TAF_APS_FindSutiablePdpForPppDial_LteMode(&pstPppDialOrigReq->stPppDialParaInfo,
                                                             &ulErrCode);
        if (TAF_ERR_ERROR == ulErrCode)
        {
            TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                     TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }

        /* �ҵ�Ĭ�ϳ��ص�����£�ֱ��ˢ��CID */
        if (VOS_TRUE == ulResult)
        {
            /* ����ˢ��CID����ͬʱˢ����ClientId��OP ID */
            ucPdpId = TAF_APS_GetPdpIdByDefaultCid();

            /* ���cid 0 ����Ϣ,��¼PDP ��Ϣ */
            TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                        pstPppDialOrigReq->stPppDialParaInfo.ucCid,
                                        pstPppDialOrigReq->stCtrl.ulModuleId,
                                        pstPppDialOrigReq->stCtrl.usClientId,
                                        pstPppDialOrigReq->stCtrl.ucOpId);

            TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                         pstPppDialOrigReq->stPppDialParaInfo.ucCid,
                                         TAF_APS_GetTafCidInfoPdpType(pstPppDialOrigReq->stPppDialParaInfo.ucCid));

            /* ֪ͨESM��ǰ��Cidˢ�� */
            MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                    SM_ESM_PDP_OPT_MODIFY);

            return VOS_FALSE;
        }
    }

#endif

    /* ��ȡPdpId�������ȡ������˵����ǰ�Ǽ������ȥ����һ���µ�CID */
    ucPdpId = TAF_APS_GetPdpIdByCid(pstPppDialOrigReq->stPppDialParaInfo.ucCid);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* ����ʵ�� */
        if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&pstPppDialOrigReq->stCtrl,
                                                           pstPppDialOrigReq->stPppDialParaInfo.ucCid,
                                                           &ucPdpId))
        {
            /* ���䲻��ʵ�壬��ֱ�ӷ���ERROR */
            TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                     TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }
    }
    else
    {
        if (TAF_APS_GetPdpEntClientId(ucPdpId, pstPppDialOrigReq->stPppDialParaInfo.ucCid) != pstPppDialOrigReq->stCtrl.usClientId)
        {
            /* ClientId��ƥ��, ��ֱ�ӷ���ERROR */
            TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                     TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }
    }

    if (VOS_TRUE == TAF_APS_IsPdpActLimit_PreProc())
    {
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                 TAF_PS_CAUSE_PDP_ACTIVATE_LIMIT);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_PreProc
 ��������  : �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ��ʱ����Ҫ����Ԥ�����ж���ǰ�Ƿ��ܽ���״̬��
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���
  2.��    ��   : 2012��3��6��
    ��    ��   : c00173809
    �޸�����   : PPP��NDIS����ͬCID��PDP�����ĳ���.

  3.��    ��   : 2013��9��23��
    ��    ��   : A00165503
    �޸�����   : UART-MODEM: PDPID��ȡʧ��ʱ����ERROR, ��ֹ�û�����
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;
    TAF_APS_BITCID_INFO_STRU            stCid;

    PS_MEM_SET(&stCid, 0, sizeof(TAF_APS_BITCID_INFO_STRU));
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq                       = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* ��ȡPdpId�������ȡ������ֱ�ӷ��أ�����״̬�� */
    ucPdpId = TAF_APS_GetPdpIdByCid(pstCallEndReq->ucCid);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* �ó����·���ERROR, ��ֹʹ���߹��� */
        TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl),
                              pstCallEndReq->ucCid,
                              TAF_PS_CAUSE_CID_INVALID);
        return VOS_TRUE;

    }
    else
    {
        if (TAF_APS_GetPdpEntClientId(ucPdpId, pstCallEndReq->ucCid) != pstCallEndReq->stCtrl.usClientId)
        {
            TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl),
                                  pstCallEndReq->ucCid,
                                  TAF_PS_CAUSE_CID_INVALID);

            return VOS_TRUE;
        }
        else
        {
            /* �����û���Ϣ--IMSA��ʹ�ò�ͬ��opid */
            TAF_APS_SetPdpEntOpId(ucPdpId,
                                  pstCallEndReq->ucCid,
                                  pstCallEndReq->stCtrl.ucOpId);

            /* ���PDPʵ�����Ƿ���ڶ��cid */
            TAF_APS_GetPdpEntBitCidInfo(ucPdpId, &stCid);

            if (stCid.ulNum > 1)
            {
                /* ���ظ�cidȥ����ɹ� */
                TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl),
                                      pstCallEndReq->ucCid,
                                      TAF_PS_CAUSE_SUCCESS);

                TAF_APS_SndPdpDeActivateCnf(ucPdpId, pstCallEndReq->ucCid);

                /* ���PDPʵ���и�CID��Ϣ */
                TAF_APS_RmvPdpEntClientInfo(ucPdpId, pstCallEndReq->ucCid, &stCid);

                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallAnswerReq_PreProc
 ��������  : �յ�ANSWER��Ϣ��ʱ����Ҫ����Ԥ�����ж���ǰ�Ƿ��ܽ���״̬��
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
  1.��    ��  : 2011��12��22��
    ��    ��  : h44270
    �޸�����  : �����ɺ���
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
  3.��    ��   : 2013��05��22��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP PROJECT
  4.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ�����ݽṹ���������PID��¼��ʵ��

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;
    TAF_PRI_PDP_QUERY_INFO_STRU         stPdpPriPara;
    VOS_UINT32                          ulErrCode;
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU    *pstNwActFsm;
    VOS_UINT8                           ucPdpId;

    VOS_UINT8                           ucCid;

    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq                    = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);
    ucCid                               = pstCallAnswerReq->stAnsInfo.ucCid;

    pstNwActFsm = TAF_APS_GetPdpEntityFsm(TAF_APS_STA_NW_ACTIVATING,
                                          TAF_APS_FSM_NW_ACTIVATING,
                                          TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER);

    /* �жϵ�ǰ�Ƿ������缤��ȴ��û�Ӧ��״̬ */
    if (VOS_NULL_PTR == pstNwActFsm)
    {
        TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                 pstCallAnswerReq->stAnsInfo.ucCid,
                                 TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }

    ucPdpId = pstNwActFsm->ucPdpId;

    /* ��֧��IPV4/IPV4V6���ͣ�ֱ�ӻ�ERROR */
#if (FEATURE_ON == FEATURE_IPV6)
    if ((MN_APS_ADDR_IPV6 == g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum)
     || (MN_APS_ADDR_IPV4V6 == g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum))
    {
        TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                 pstCallAnswerReq->stAnsInfo.ucCid,
                                 TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }
#endif

    /* �û�ָ����CID����Ҫƥ��PDP TYPE��ADDR������ʹ������ָ����PDP TYPE��ADDR */
    if (0 != ucCid)
    {
        /* ��ȡPrimary PDP��������Ϣ */
        PS_MEM_SET(&stPdpPriPara, 0x00, sizeof(TAF_PRI_PDP_QUERY_INFO_STRU));
        Aps_QuePri(pstCallAnswerReq->stAnsInfo.ucCid, &stPdpPriPara, &ulErrCode);
        if (TAF_PARA_OK != ulErrCode)
        {
            TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                     pstCallAnswerReq->stAnsInfo.ucCid,
                                     TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }
        else
        {
            /* �û����õ����ͺ������·������Ͳ�һ�� */
            if (TAF_APS_ConvertPdpType(g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum) != stPdpPriPara.stPriPdpInfo.stPdpAddr.enPdpType)
            {
                TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                         pstCallAnswerReq->stAnsInfo.ucCid,
                                         TAF_PS_CAUSE_UNKNOWN);
                return VOS_TRUE;
            }

            /* ���緢���PPP���͵Ĳ��ţ���Ҫ����ƥ�䲦������ */
            /* ���緢���IPV4���͵Ĳ��ţ���Ҫ����ƥ�䲦�����ͺ�IP��ַ */
            if (APS_ADDR_PPP != g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum)
            {
                /* �û�������PDP ADDR */
                if ('\0' != stPdpPriPara.stPriPdpInfo.stPdpAddr.aucIpv4Addr[0])
                {
                    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
                    if (0 != PS_MEM_CMP(stPdpPriPara.stPriPdpInfo.stPdpAddr.aucIpv4Addr,
                                        g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr,
                                        TAF_IPV4_ADDR_LEN))
                    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
                    {
                        TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                                 pstCallAnswerReq->stAnsInfo.ucCid,
                                                 TAF_PS_CAUSE_UNKNOWN);
                        return VOS_TRUE;
                    }
                }
            }
        }
    }

    ucCid = ((0 != ucCid) ? ucCid : TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* ��¼PDP ��Ϣ */
    TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                ucCid,
                                pstCallAnswerReq->stCtrl.ulModuleId,
                                pstCallAnswerReq->stCtrl.usClientId,
                                pstCallAnswerReq->stCtrl.ucOpId);

    TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_ConvertPdpType(g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum));

    /* ���AT^ANSWER�����IP���͵����缤����Ӧ��ֱ���ϱ�CONNECT��AT���ȴ�PPP���𲦺����� */
    if (VOS_TRUE == pstCallAnswerReq->stAnsInfo.ucAnsExtFlg)
    {
        if (TAF_PDP_IPV4 == TAF_APS_ConvertPdpType(g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum))
        {
            /* ǰ������ɹ�����¼��Ӧ��Ŀͻ��˺ͺ��б�ʶ��Cid */
            g_PdpEntity[ucPdpId].PdpProcTrack.ucHowToInitAct
                                                = APS_APP_MANUL_ACT;

            TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                     TAF_APS_GetPdpEntCurrCid(ucPdpId),
                                     TAF_ERR_AT_CONNECT);

            return VOS_TRUE;
        }
    }


    /* Ԥ�����������Ҫ����״̬�� */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallHangupReq_PreProc
 ��������  : �յ�HAANUP��Ϣ��ʱ����Ҫ����Ԥ�����ж���ǰ�Ƿ��ܽ���״̬��
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���

  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU    *pstNwActFsm;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq                    = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    pstNwActFsm = TAF_APS_GetPdpEntityFsm(TAF_APS_STA_NW_ACTIVATING,
                                          TAF_APS_FSM_NW_ACTIVATING,
                                          TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER);

    /* �жϵ�ǰ�Ƿ������缤��ȴ��û�Ӧ��״̬ */
    if (VOS_NULL_PTR == pstNwActFsm)
    {
        TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl), TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmRegPdpActCnf_PreProc
 ��������  : �յ�SM D_PMC_SMREG_PDP_ACT_CNF��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���

 2.��    ��  : 2011��12��22��
   ��    ��  : M00217266
   �޸�����  : ����PDP����ʧ�ܼ�������AT&T&DCM���� PDP�������ޣ�
 3.��    ��   : 2012��8��10��
   ��    ��   : L00171473
   �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpActCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_ACTIVATE_CNF_STRU        *pstSmMsg;
    SM_TAF_TRANS_ID_STRU                stTi;
    TAF_APS_PDP_ACT_LIMIT_INFO_STRU    *pstPdpActLimitInfo;


    PS_MEM_SET(&stTi, 0x00, sizeof(stTi));


    pstSmMsg = (SMREG_PDP_ACTIVATE_CNF_STRU *)pstMsg;

    /* ����CR��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    pstPdpActLimitInfo = TAF_APS_GetPdpActLimitInfoAddr();

    if (VOS_TRUE == pstPdpActLimitInfo->ucPdpActLimitFlg)
    {
        pstPdpActLimitInfo->ucPdpActFailCount = 0;

        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID))
        {
            TAF_APS_StopTimer(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID);
        }
    }


    /* mo������ֱ���ڴ˴�ˢ��ʵ����Ti��ֵ */
    stTi.ucTiValue = pstSmMsg->stTransId.ucTiValue;
    stTi.ucTiFlag  = pstSmMsg->stTransId.ucTiFlag;

    TAF_APS_SetPdpEntityTi(pstSmMsg->ucConnectId, &stTi);

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmRegPdpActRej_PreProc
 ��������  : �յ�SM D_PMC_SMREG_PDP_ACT_REJ��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���

 2.��    ��  : 2012��6��15��
   ��    ��  : m00217266
   �޸�����  : ���PDP�������޴���

  3.��    ��   : 2012��8��22��
    ��    ��   : A00165503
    �޸�����   : SM/APSԭ��ӿ��е�CAUSE��Ա�����޸�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpActRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_ACTIVATE_REJ_STRU        *pstSmMsg;

    pstSmMsg = (SMREG_PDP_ACTIVATE_REJ_STRU *)pstMsg;

    /* ����CR��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    /* PDP�������޴���:PDP����Ĵ���ΪSMʵ�ʳ��Ե�PDP������� */
    if (SM_TAF_CAUSE_SM_MAX_TIME_OUT == pstSmMsg->enCause)
    {
        TAF_APS_ProcPdpActLimit_PreProc(pstSmMsg->ucExpiredCount);
    }
    else
    {
        TAF_APS_ProcPdpActLimit_PreProc(pstSmMsg->ucExpiredCount + 1);
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmRegPdpActInd_PreProc
 ��������  : �յ�SM D_PMC_SMREG_PDP_ACT_Ind��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���
 2.��    ��   : 2012��8��10��
   ��    ��   : L00171473
   �޸�����   : DTS2012082204471, TQE����
 3.��    ��   : 2013��06��05��
   ��    ��   : f00179208
   �޸�����   : V3R3 PPP PROJECT
 4.��    ��   : 2013��07��08��
   ��    ��   : Y00213812
   �޸�����   : VoLTE_PhaseI ��Ŀ������PID��¼��ʵ��
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpActInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_ACTIVATE_IND_STRU        *pstSmMsg;
    APS_PDP_CONTEXT_ENTITY_ST          *pstCurrEntity;
    SM_TAF_TRANS_ID_STRU                stTi;


    PS_MEM_SET(&stTi, 0x00, sizeof(stTi));


    pstSmMsg = (SMREG_PDP_ACTIVATE_IND_STRU *)pstMsg;


    /* ���緢���PDP�����Ԥ��������PDP ID,�����CR ��ͬ��PDP ID */
    pstCurrEntity = TAF_APS_GetPdpEntInfoAddr(pstSmMsg->ucConnectId);
    pstCurrEntity->stClientInfo.ucCid   = TAF_APS_FindCidForAns();
    pstCurrEntity->ulUsedFlg            = VOS_TRUE;
    pstCurrEntity->ucPdpId              = pstSmMsg->ucConnectId;

    /* ˢ��PDP��Ϣ */
    TAF_APS_SetPdpEntClientInfo(pstCurrEntity->ucPdpId,
                                pstCurrEntity->stClientInfo.ucCid,
                                TAF_APS_INVALID_MODULEID,
                                TAF_APS_INVALID_CLIENTID,
                                TAF_APS_INVALID_OPID);

    /* mt������ֱ���ڴ˴�ˢ��ʵ����Ti��ֵ */
    stTi.ucTiValue = pstSmMsg->stTransId.ucTiValue;
    stTi.ucTiFlag  = pstSmMsg->stTransId.ucTiFlag;

    TAF_APS_SetPdpEntityTi(pstSmMsg->ucConnectId, &stTi);

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmRegPdpModifyInd_PreProc
 ��������  : �յ�SM SMREG_PDP_MODIFY_IND_STRU��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_MODIFY_IND_STRU          *pstSmMsg;

    pstSmMsg = (SMREG_PDP_MODIFY_IND_STRU *)pstMsg;

    /* ����CR��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    return VOS_FALSE;


}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmRegPdpModifyCnf_PreProc
 ��������  : �յ�SM D_PMC_SMREG_PDP_MODIFY_IND��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpModifyCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_MODIFY_CNF_STRU          *pstSmMsg;

    pstSmMsg = (SMREG_PDP_MODIFY_CNF_STRU *)pstMsg;

    /* ����CR��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    return VOS_FALSE;

}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmRegPdpModifyRej_PreProc
 ��������  : �յ�SM D_PMC_SMREG_PDP_MODIFY_IND��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpModifyRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_MODIFY_REJ_STRU          *pstSmMsg;

    pstSmMsg = (SMREG_PDP_MODIFY_REJ_STRU *)pstMsg;

    /* ����CR��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    return VOS_FALSE;


}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmRegPdpDeactivInd_PreProc
 ��������  : �յ�SM D_PMC_SMREG_PDP_DEACTIV_IND��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���

2.��    ��  : 2012��6��15��
   ��    ��  : m00217266
   �޸�����  : ���PDP�������޴���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpDeactivInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmMsg;

    pstSmMsg = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    /* ����TI��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    /* PDP�������޴���: �������������PDPȥ�����Ϊ����PDP����Ĵ���Ϊ1 */
    TAF_APS_ProcPdpActLimit_PreProc(1);

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmRegPdpDeactivCnf_PreProc
 ��������  : �յ�SM D_PMC_SMREG_PDP_DEACTIV_CNF��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpDeactivCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_DEACTIVATE_CNF_STRU      *pstSmMsg;

    pstSmMsg = (SMREG_PDP_DEACTIVATE_CNF_STRU *)pstMsg;

    /* ����CR��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    return VOS_FALSE;


}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmRegPdpActSecCnf_PreProc
 ��������  : �յ�SM D_PMC_SMREG_PDP_ACT_SEC_CNF��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���
 2.��    ��   : 2012��8��10��
   ��    ��   : L00171473
   �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpActSecCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_ACTIVATE_SEC_CNF_STRU    *pstSmMsg;
    SM_TAF_TRANS_ID_STRU                stTi;


    PS_MEM_SET(&stTi, 0x00, sizeof(stTi));


    pstSmMsg = (SMREG_PDP_ACTIVATE_SEC_CNF_STRU *)pstMsg;

    /* ����CR��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    /* mo������ֱ���ڴ˴�ˢ��ʵ����Ti��ֵ */
    stTi.ucTiValue = pstSmMsg->stTransId.ucTiValue;
    stTi.ucTiFlag  = pstSmMsg->stTransId.ucTiFlag;

    TAF_APS_SetPdpEntityTi(pstSmMsg->ucConnectId, &stTi);

    return VOS_FALSE;


}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSmRegPdpActSecRej_PreProc
 ��������  : �յ�SM D_PMC_SMREG_PDP_ACT_SEC_REJ��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSmRegPdpActSecRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_ACTIVATE_SEC_REJ_STRU    *pstSmMsg;

    pstSmMsg = (SMREG_PDP_ACTIVATE_SEC_REJ_STRU *)pstMsg;

    /* ����CR��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    return VOS_FALSE;


}

#if ( FEATURE_ON == FEATURE_LTE )
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetEpsQosInfoReq_PreProc
 ��������  : ����EPS��������Ԥ������
             (ID_MSG_TAF_PS_SET_EPS_QOS_INFO_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetEpsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                           TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

    /* ������Ϣ��L4A */
    TAF_APS_SndL4aSetCgeqosReq(pstPsMsg->aucContent);

    /* ����L4A��Ϣ�ظ�������ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGEQOS_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* �����Ϣ���ȴ����� */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOS_CNF,
                                     (VOS_UINT32 *)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_SET_EPS_QOS_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvL4aSetCgdcontCnf_PreProc
 ��������  : CNF��ϢԤ������
             (ID_L4A_APS_SET_CGDCONT_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��6��15��
    ��    ��   : m00217266
    �޸�����   : ֹͣ��ͣPDP���ʱ��(AT&T���ƣ�PDP��������)

  3.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ�����ݽṹ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgdcontCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGDCONT_CNF_STRU               *pstPsMsg;
    TAF_CTRL_STRU                               stCtrl = {0};
    VOS_UINT32                                  ulErrCode;
    TAF_APS_CMD_BUFFER_STRU                    *pstMsgInfo;
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU  *pstSetPdpCtxInfoReq;
    VOS_UINT32                                  ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (APS_L4A_SET_CGDCONT_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetPdpCtxInfoReq     = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGDCONT_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGDCONT_CNF, ulPara);

        /* �ӻ�������л�ȡ��Ϣ */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDCONT_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgdcontCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }
        /* ��Ϣ��ȡ�ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        pstSetPdpCtxInfoReq = (TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;
        stCtrl = pstSetPdpCtxInfoReq->stCtrl;

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4Aȫ�ֱ������³ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {

            /* PDP�����������Դ򿪣���ͣ���ʱ���������� */
            if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID))
            {
                TAF_APS_RcvSetPrimPdpCtxInfoReq_PdpActLimit(pstSetPdpCtxInfoReq);
            }


            /* ����Primary PDP������ */
            Aps_DefPsPdpContext(pstSetPdpCtxInfoReq->stCtrl.usClientId,
                                pstSetPdpCtxInfoReq->stCtrl.ucOpId,
                                &(pstSetPdpCtxInfoReq->stPdpContextInfo),
                                &ulErrCode);
        }

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDCONT_CNF, ulPara);

        /* ����AT������ */
        TAF_APS_SndSetPrimPdpCtxInfoCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvL4aSetCgdscontCnf_PreProc
 ��������  : CNF��ϢԤ������
             (ID_L4A_APS_SET_CGDSCONT_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
  2.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ�����ݽṹ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgdscontCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGDSCONT_CNF_STRU              *pstPsMsg;
    TAF_CTRL_STRU                               stCtrl = {0};
    VOS_UINT32                                  ulErrCode;
    TAF_APS_CMD_BUFFER_STRU                    *pstMsgInfo;
    TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU   *pstSetPdpCtxInfoReq;
    VOS_UINT32                                  ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (APS_L4A_SET_CGDSCONT_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetPdpCtxInfoReq     = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF, ulPara);

        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
        /* �ӻ�������л�ȡ��Ϣ */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgdscontCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* ��Ϣ��ȡ�ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        pstSetPdpCtxInfoReq = (TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;
        stCtrl = pstSetPdpCtxInfoReq->stCtrl;

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4Aȫ�ֱ������³ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* ����Primary PDP������ */
            Aps_DefPsSecPdpContext(pstSetPdpCtxInfoReq->stCtrl.usClientId,
                                   pstSetPdpCtxInfoReq->stCtrl.ucOpId,
                                   &(pstSetPdpCtxInfoReq->stPdpContextInfo),
                                   &ulErrCode);
        }
        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF, ulPara);

        /* ����AT������ */
        TAF_APS_SndSetSecPdpCtxInfoCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvL4aSetCgtftCnf_PreProc
 ��������  : CNF��ϢԤ������
             (ID_L4A_APS_SET_CGTFT_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
  2.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ�����ݽṹ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgtftCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGTFT_CNF_STRU         *pstPsMsg;
    TAF_CTRL_STRU                       stCtrl = {0};
    VOS_UINT32                          ulErrCode;
    TAF_APS_CMD_BUFFER_STRU            *pstMsgInfo;
    TAF_PS_SET_TFT_INFO_REQ_STRU       *pstSetTftInfoReq;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (APS_L4A_SET_CGTFT_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetTftInfoReq        = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGTFT_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGTFT_CNF, ulPara);

        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
        /* �ӻ�������л�ȡ��Ϣ */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFT_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgtftCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* ��Ϣ��ȡ�ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        pstSetTftInfoReq = (TAF_PS_SET_TFT_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;
        stCtrl = pstSetTftInfoReq->stCtrl;

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4Aȫ�ֱ������³ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* ����TFT���� */
            TAF_APS_SetTftInfo(&(pstSetTftInfoReq->stTftInfo), &ulErrCode);
        }
        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFT_CNF, ulPara);

        /* ����AT������ */
        TAF_APS_SndSetTftInfoCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvL4aSetCgautoCnf_PreProc
 ��������  : CNF��ϢԤ������
             (ID_L4A_APS_SET_CGAUTO_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgautoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGAUTO_CNF_STRU            *pstPsMsg;
    TAF_CTRL_STRU                           stCtrl = {0};
    VOS_UINT32                              ulErrCode;
    TAF_APS_CMD_BUFFER_STRU                *pstMsgInfo;
    TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU   *pstSetAnsModeInfoReq;
    VOS_UINT32                              ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (APS_L4A_SET_CGAUTO_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetAnsModeInfoReq    = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);


    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGAUTO_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGAUTO_CNF, ulPara);

        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
        /* �ӻ�������л�ȡ��Ϣ */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGAUTO_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgautoCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* ��Ϣ��ȡ�ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        pstSetAnsModeInfoReq = (TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;
        stCtrl = pstSetAnsModeInfoReq->stCtrl;

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4Aȫ�ֱ������³ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* ���Ӧ��ģʽ�Ƿ�Ϸ� */
            if ( (TAF_PDP_ANSWER_MODE_MANUAL == pstSetAnsModeInfoReq->ulAnsMode)
              || (TAF_PDP_ANSWER_MODE_AUTO   == pstSetAnsModeInfoReq->ulAnsMode) )
            {
                /* ����Ӧ��ģʽ */
                Aps_SetPsAnsMode(pstSetAnsModeInfoReq->stCtrl.usClientId,
                                 pstSetAnsModeInfoReq->stCtrl.ucOpId,
                                 (TAF_PDP_ANSWER_MODE_ENUM_UINT8)pstSetAnsModeInfoReq->ulAnsMode,
                                 &ulErrCode);
            }
            else
            {
                ulErrCode = TAF_PARA_SET_ERROR;
            }
        }
        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGAUTO_CNF, ulPara);

        /* ����AT������ */
        TAF_APS_SndSetAnsModeInfoCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvL4aSetCgansCnf_PreProc
 ��������  : CNF��ϢԤ������
             (ID_L4A_APS_SET_CGANS_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgansCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����L4A��������Ϣ */

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvL4aSetCgeqosCnf_PreProc
 ��������  : CNF��ϢԤ������
             (ID_L4A_APS_SET_CGEQOS_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgeqosCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGEQOS_CNF_STRU        *pstPsMsg;
    TAF_CTRL_STRU                       stCtrl = {0};
    VOS_UINT32                          ulErrCode;
    TAF_APS_CMD_BUFFER_STRU            *pstMsgInfo;
    TAF_PS_SET_EPS_QOS_INFO_REQ_STRU   *pstSetEpsQosInfoReq;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (APS_L4A_SET_CGEQOS_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetEpsQosInfoReq     = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGEQOS_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGEQOS_CNF, ulPara);

        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
        /* �ӻ�������л�ȡ��Ϣ */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOS_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgeqosCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* ��Ϣ��ȡ�ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        pstSetEpsQosInfoReq = (TAF_PS_SET_EPS_QOS_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;
        stCtrl = pstSetEpsQosInfoReq->stCtrl;

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4Aȫ�ֱ������³ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* ����Ӧ��ģʽ */
            TAF_APS_SetEpsQosInfo(&pstSetEpsQosInfoReq->stEpsQosInfo,
                                  &ulErrCode);
        }
        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOS_CNF, ulPara);

        /* ����AT������ */
        TAF_APS_SndSetCgeqosCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvL4aSetAuthdataCnf_PreProc
 ��������  : CNF��ϢԤ������
             (ID_L4A_APS_SET_AUTHDATA_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetAuthdataCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_AUTHDATA_CNF_STRU      *pstPsMsg;
    TAF_CTRL_STRU                       stCtrl = {0};
    VOS_UINT32                          ulErrCode;
    TAF_APS_CMD_BUFFER_STRU            *pstMsgInfo;
    TAF_PS_SET_AUTHDATA_INFO_REQ_STRU  *pstAuthDataReq;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (APS_L4A_SET_AUTHDATA_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstAuthDataReq          = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF, ulPara);

        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
        /* �ӻ�������л�ȡ��Ϣ */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetAuthdataCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* ��Ϣ��ȡ�ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        pstAuthDataReq = (TAF_PS_SET_AUTHDATA_INFO_REQ_STRU *)pstMsgInfo->pulMsgInfo;
        stCtrl = pstAuthDataReq->stCtrl;

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4Aȫ�ֱ������³ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* ����AUTHDATA����(NDIS) */
            Aps_DefNdisAuthdata(pstAuthDataReq->stCtrl.usClientId,
                                pstAuthDataReq->stCtrl.ucOpId,
                                &(pstAuthDataReq->stAuthDataInfo),
                                &ulErrCode);
        }
        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF, ulPara);

        /* ����AT������ */
        (VOS_VOID)TAF_APS_SndSetAuthDataInfoCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvL4aSetCgcontrdpCnf_PreProc
 ��������  : CNF��ϢԤ������
             (ID_L4A_APS_SET_CGCONTRDP_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgcontrdpCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGCONTRDP_CNF_STRU                     *pstPsMsg;
    VOS_UINT32                                          ulErrCode;
    VOS_UINT32                                          ulCidNum;                   /* CID����  */
    TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU  *pstGetDynamicPdpCtxInfoCnf;
    VOS_UINT32                                          ulGetDynamicPdpCtxInfoCnfLen;
    VOS_UINT32                                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                            = (APS_L4A_SET_CGCONTRDP_CNF_STRU*)pstMsg;
    ulErrCode                           = pstPsMsg->ulErrorCode;
    ulCidNum                            = pstPsMsg->ulCidNum;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF, ulPara);

        /* L4A�������ת�� */
        ulErrCode   = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4A��ѯ��̬����ʧ�ܣ�CID����Ϊ0 */
        if ( TAF_PS_CAUSE_SUCCESS != ulErrCode )
        {
            ulCidNum = 0;
        }

        /* ����ظ��¼���Ϣ���ݳ��� */
        ulGetDynamicPdpCtxInfoCnfLen    = sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU)
                                            + (ulCidNum * sizeof(TAF_PDP_DYNAMIC_PRIM_EXT_STRU));

        /* �����ڴ� */
        pstGetDynamicPdpCtxInfoCnf      = (TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                                                                           ulGetDynamicPdpCtxInfoCnfLen);

        /* ������Ϣʧ�� */
        if ( VOS_NULL_PTR == pstGetDynamicPdpCtxInfoCnf )
        {
            /* ϵͳ�쳣��ӡ, ֱ�ӷ��� */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgcontrdpCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        /* ��д�¼����� */
        PS_MEM_SET(pstGetDynamicPdpCtxInfoCnf,
                   0x00,
                   ulGetDynamicPdpCtxInfoCnfLen);


        /* �ӻ�������л�ȡ��Ϣ */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstGetDynamicPdpCtxInfoCnf->stCtrl,
                                                              TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF,
                                                              ulPara))
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgcontrdpCnf_PreProc: Get message info failed!");

            /* �ͷ��ڴ� */
            PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicPdpCtxInfoCnf);

            return VOS_TRUE;
        }

        pstGetDynamicPdpCtxInfoCnf->enCause         = ulErrCode;
        pstGetDynamicPdpCtxInfoCnf->ulCidNum        = ulCidNum;

        if (0 != ulCidNum)
        {
            PS_MEM_CPY(pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo,
                       pstPsMsg->astPrimParaInfo,
                       (ulCidNum * sizeof(TAF_PDP_DYNAMIC_PRIM_EXT_STRU)));
        }

        /* ����Ϣ����AT */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF,
                        pstGetDynamicPdpCtxInfoCnf,
                        ulGetDynamicPdpCtxInfoCnfLen);

        /* �ͷ��ڴ� */
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicPdpCtxInfoCnf);

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF, ulPara);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvL4aSetCgscontrdpCnf_PreProc
 ��������  : CNF��ϢԤ������
             (ID_L4A_APS_SET_CGSCONTRDP_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
  2.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ���ӻ�������л�ȡ��Ϣ

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgscontrdpCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGSCONTRDP_CNF_STRU                    *pstPsMsg;
    VOS_UINT32                                          ulErrCode;
    VOS_UINT32                                          ulCidNum;                   /* CID����  */
    TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU   *pstGetDynamicPdpCtxInfoCnf;
    VOS_UINT32                                          ulGetDynamicPdpCtxInfoCnfLen;
    VOS_UINT32                                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                            = (APS_L4A_SET_CGSCONTRDP_CNF_STRU*)pstMsg;
    ulErrCode                           = pstPsMsg->ulErrorCode;
    ulCidNum                            = pstPsMsg->ulCidNum;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF, ulPara);

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4A��ѯ��̬����ʧ�ܣ�CID����Ϊ0 */
        if ( TAF_PS_CAUSE_SUCCESS != ulErrCode )
        {
            ulCidNum = 0;
        }

        /* �����¼����ݳ��� */
        ulGetDynamicPdpCtxInfoCnfLen    = sizeof(TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU)
                                            + (ulCidNum * sizeof(TAF_PDP_DYNAMIC_SEC_EXT_STRU));

        /* �����ڴ� */
        pstGetDynamicPdpCtxInfoCnf      = (TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                                                                          ulGetDynamicPdpCtxInfoCnfLen);

        /* ������Ϣʧ�� */
        if ( VOS_NULL_PTR == pstGetDynamicPdpCtxInfoCnf )
        {
            /* ϵͳ�쳣��ӡ, ֱ�ӷ��� */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgscontrdpCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        /* ��д�¼����� */
        PS_MEM_SET(pstGetDynamicPdpCtxInfoCnf,
                   0x00,
                   ulGetDynamicPdpCtxInfoCnfLen);

        /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
        /* �ӻ�������л�ȡ��Ϣ */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstGetDynamicPdpCtxInfoCnf->stCtrl,
                                                              TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF,
                                                              ulPara))
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgscontrdpCnf_PreProc: Get message info failed!");

            /* �ͷ��ڴ� */
            PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicPdpCtxInfoCnf);

            return VOS_TRUE;
        }
        /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

        pstGetDynamicPdpCtxInfoCnf->enCause          = ulErrCode;
        pstGetDynamicPdpCtxInfoCnf->ulCidNum         = ulCidNum;

        if (0 != ulCidNum)
        {
            PS_MEM_CPY(pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo,
                       pstPsMsg->astSecParaInfo,
                       (ulCidNum * sizeof(TAF_PDP_DYNAMIC_SEC_EXT_STRU)));
        }

        /* ����Ϣ����AT */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF,
                         pstGetDynamicPdpCtxInfoCnf,
                         ulGetDynamicPdpCtxInfoCnfLen);

        /* �ͷ��ڴ� */
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicPdpCtxInfoCnf);

        /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF, ulPara);
        /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_FillPfTftInfo
 ��������  : ��L4a�ظ���TFT������䵽�ظ���AT��CNF��Ϣ��
 �������  : APS_L4A_SDF_PF_TFT_STRU   *pstL4aPfTftInfo - L4A�ظ���TFT����
             VOS_UINT32                 ulCidNum        - CID����
  �������  : TAF_PF_TFT_STRU           *pstPfTftInfo    - ��AT�ظ���TFT����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��01��12��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��9��28��
    ��    ��   : W00316404
    �޸�����   : R11 TFT Э������

*****************************************************************************/
VOS_VOID TAF_APS_FillPfTftInfo(
    TAF_PF_TFT_STRU                    *pstPfTftInfo,
    APS_L4A_SDF_PF_TFT_STRU            *pstL4aPfTftInfo,
    VOS_UINT32                          ulCidNum
)
{
    VOS_UINT32                          ulIndex1;
    VOS_UINT32                          ulIndex2;

    /* ��ʼ������ */
    ulIndex1        = VOS_NULL;
    ulIndex2        = VOS_NULL;

    /* ѭ���������TFT���� */
    for (ulIndex1 = 0; ulIndex1 < ulCidNum; ulIndex1++)
    {
        pstPfTftInfo[ulIndex1].ulCid    = pstL4aPfTftInfo[ulIndex1].ulCid;
        pstPfTftInfo[ulIndex1].ulPFNum  = pstL4aPfTftInfo[ulIndex1].ulPfNum;

        for (ulIndex2 = 0; ulIndex2 < pstL4aPfTftInfo[ulIndex1].ulPfNum; ulIndex2++)
        {
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpPktFilterId    = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpPktFilterId;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpPrecedence     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpPrecedence;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSrcIp          = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSrcIp;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpProtocolId     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpProtocolId;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpDestPortRange  = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpDestPortRange;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSrcPortRange   = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSrcPortRange;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSpi            = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSpi;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpTosMask        = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpTosMask;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpFlowLable      = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpFlowLable;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpDirection      = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpDirection;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpNwPktFilterId  = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpNwPktFilterId;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpLocalIpv4AddrAndMask  = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpLocalIpv4AddrAndMask;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpLocalIpv6AddrAndMask  = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpLocalIpv6AddrAndMask;

            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucCid               = (VOS_UINT8)pstL4aPfTftInfo[ulIndex1].ulCid;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucDefined           = VOS_TRUE;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucPacketFilterId    = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucPacketFilterId;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucPrecedence        = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucPrecedence;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucProtocolId        = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucProtocolId;

            PS_MEM_CPY(&(pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].stSourceIpaddr),
                       &(pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].stSourceIpaddr),
                       sizeof(TAF_PDP_ADDR_STRU));
            PS_MEM_CPY(&(pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].stSourceIpMask),
                       &(pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].stSourceIpMask),
                       sizeof(TAF_PDP_ADDR_STRU));
            PS_MEM_CPY(pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].aucLocalIpv4Addr,
                       pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].aucLocalIpv4Addr,
                       APS_L4A_MAX_IPV4_ADDR_LEN);
            PS_MEM_CPY(pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].aucLocalIpv4Mask,
                       pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].aucLocalIpv4Mask,
                       APS_L4A_MAX_IPV4_ADDR_LEN);
            PS_MEM_CPY(pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].aucLocalIpv6Addr,
                       pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].aucLocalIpv6Addr,
                       APS_L4A_MAX_IPV6_ADDR_LEN);
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucLocalIpv6Prefix   = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucLocalIpv6Prefix;

            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usLowSourcePort     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usLowSourcePort;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usHighSourcePort    = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usHighSourcePort;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usLowDestPort       = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usLowDestPort;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usHighDestPort      = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usHighDestPort;

            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ulSecuParaIndex     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ulSecuParaIndex;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ulFlowLable         = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ulFlowLable;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucTypeOfServiceMask = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucTypeOfServiceMask;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucTypeOfService     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucTypeOfService;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucDirection         = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].enTftFilterDirection;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucNwPktFilterId     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucNwPktFilterId;
        }

    }
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvL4aSetCgtftrdpCnf_PreProc
 ��������  : CNF��ϢԤ������
             (ID_L4A_APS_SET_CGTFTRDP_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ���ӻ�������л�ȡ��Ϣ

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgtftrdpCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGTFTRDP_CNF_STRU          *pstPsMsg;
    VOS_UINT32                              ulErrCode;
    VOS_UINT32                              ulCidNum;                   /* CID����  */
    TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU   *pstGetDynamicTftInfoCnf;
    VOS_UINT32                              ulGetDynamicTftInfoCnfLen;
    VOS_UINT32                              ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                            = (APS_L4A_SET_CGTFTRDP_CNF_STRU*)pstMsg;
    ulErrCode                           = pstPsMsg->ulErrorCode;
    ulCidNum                            = pstPsMsg->ulCidNum;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF, ulPara);

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4A��ѯ��̬����ʧ�ܣ�CIDNum����Ϊ0 */
        if ( TAF_PS_CAUSE_SUCCESS != ulErrCode )
        {
            ulCidNum = 0;
        }

        /* �����¼����ݳ��� */
        ulGetDynamicTftInfoCnfLen   = sizeof(TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU)
                                        + (ulCidNum * sizeof(TAF_PF_TFT_STRU));

        /* �����ڴ� */
        pstGetDynamicTftInfoCnf = (TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                                WUEPS_PID_TAF,
                                                ulGetDynamicTftInfoCnfLen);

        /* ������Ϣʧ�� */
        if ( VOS_NULL_PTR == pstGetDynamicTftInfoCnf )
        {
            /* ϵͳ�쳣��ӡ, ֱ�ӷ��� */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgtftrdpCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        /* ��д�¼����� */
        PS_MEM_SET(pstGetDynamicTftInfoCnf,
                   0x00,
                   ulGetDynamicTftInfoCnfLen);

        /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
        /* �ӻ�������л�ȡ��Ϣ */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstGetDynamicTftInfoCnf->stCtrl,
                                                              TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF,
                                                              ulPara))
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgtftrdpCnf_PreProc: Get message info failed!");

            /* �ͷ��ڴ� */
            PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicTftInfoCnf);

            return VOS_TRUE;
        }
        /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

        pstGetDynamicTftInfoCnf->enCause          = ulErrCode;
        pstGetDynamicTftInfoCnf->ulCidNum         = ulCidNum;

        TAF_APS_FillPfTftInfo(pstGetDynamicTftInfoCnf->astPfTftInfo, pstPsMsg->astPfTftInfo, ulCidNum);

        /* ����Ϣ����AT */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_TFT_INFO_CNF,
                         pstGetDynamicTftInfoCnf,
                         ulGetDynamicTftInfoCnfLen);

        /* �ͷ��ڴ� */
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicTftInfoCnf);

        /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF, ulPara);
        /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvL4aSetCgeqosrdpCnf_PreProc
 ��������  : CNF��ϢԤ������
             (ID_L4A_APS_SET_CGEQOSRDP_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aSetCgeqosrdpCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGEQOSRDP_CNF_STRU                     *pstPsMsg;
    VOS_UINT32                                          ulErrCode;
    VOS_UINT32                                          ulCidNum;                   /* CID����  */
    TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU           *pstGetDynamicEpsQosInfoCnf;
    VOS_UINT32                                          ulGetDynamicEpsQosInfoCnfLen;
    VOS_UINT32                                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                            = (APS_L4A_SET_CGEQOSRDP_CNF_STRU*)pstMsg;
    ulErrCode                           = pstPsMsg->ulErrorCode;
    ulCidNum                            = pstPsMsg->ulCidNum;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF, ulPara);

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4A��ѯ��̬����ʧ�ܣ�CIDNum����Ϊ0 */
        if ( TAF_PS_CAUSE_SUCCESS != ulErrCode )
        {
            ulCidNum = 0;
        }

        /* �����¼����ݳ��� */
        ulGetDynamicEpsQosInfoCnfLen    = sizeof(TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU)
                                            + (ulCidNum * sizeof(TAF_EPS_QOS_EXT_STRU));

        /* �����ڴ� */
        pstGetDynamicEpsQosInfoCnf      = (TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                                                                  ulGetDynamicEpsQosInfoCnfLen);

        /* ������Ϣʧ�� */
        if ( VOS_NULL_PTR == pstGetDynamicEpsQosInfoCnf )
        {
            /* ϵͳ�쳣��ӡ, ֱ�ӷ��� */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgtftrdpCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        /* ��д�¼����� */
        PS_MEM_SET(pstGetDynamicEpsQosInfoCnf,
                   0x00,
                   ulGetDynamicEpsQosInfoCnfLen);

        /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-08-28, begin */
        /* �ӻ�������л�ȡ��Ϣ */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstGetDynamicEpsQosInfoCnf->stCtrl,
                                                              TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF,
                                                              ulPara))
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgeqosrdpCnf_PreProc: Get message info failed!");

            /* �ͷ��ڴ� */
            PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicEpsQosInfoCnf);

            return VOS_TRUE;
        }
        /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-08-28, end */

        pstGetDynamicEpsQosInfoCnf->enCause           = ulErrCode;
        pstGetDynamicEpsQosInfoCnf->ulCidNum          = ulCidNum;

        if (0 != ulCidNum)
        {
            PS_MEM_CPY(pstGetDynamicEpsQosInfoCnf->astEpsQosInfo,
                       pstPsMsg->astEpsQosInfo,
                       (ulCidNum * sizeof(TAF_EPS_QOS_EXT_STRU)));
        }

        /* ����Ϣ����AT */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF,
                         pstGetDynamicEpsQosInfoCnf,
                         ulGetDynamicEpsQosInfoCnfLen);

        /* �ͷ��ڴ� */
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicEpsQosInfoCnf);

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF, ulPara);

    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiSetCgdcontCnfExpired_PreProc
 ��������  : ����L4A��Ϣ������ʱ����ʱԤ������
             (TI_TAF_APS_WAIT_SET_CGDCONT_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgdcontCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGDCONT_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgdcontCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndSetPrimPdpCtxInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDCONT_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiSetCgdscontCnfExpired_PreProc
 ��������  : ����L4A��Ϣ������ʱ����ʱԤ������
             (TI_TAF_APS_WAIT_SET_CGDSCONT_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgdscontCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                         TI_TAF_APS_WAIT_SET_CGDSCONT_CNF,
                                                         pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgdscontCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndSetSecPdpCtxInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiSetCgtftCnfExpired_PreProc
 ��������  : ����L4A��Ϣ������ʱ����ʱԤ������
             (TI_TAF_APS_WAIT_SET_CGTFT_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgtftCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGTFT_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgtftCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndSetTftInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFT_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiSetCgautoCnfExpired_PreProc
 ��������  : ����L4A��Ϣ������ʱ����ʱԤ������
             (TI_TAF_APS_WAIT_SET_CGAUTO_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgautoCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGAUTO_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgautoCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndSetAnsModeInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGAUTO_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiSetCgeqosCnfExpired_PreProc
 ��������  : ����L4A��Ϣ������ʱ����ʱԤ������
             (TI_TAF_APS_WAIT_SET_CGEQOS_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgeqosCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGEQOS_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgeqosCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndSetCgeqosCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOS_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiSetAuthdataCnfExpired_PreProc
 ��������  : ����L4A��Ϣ������ʱ����ʱԤ������
             (TI_TAF_APS_WAIT_SET_AUTHDATA_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetAuthdataCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_AUTHDATA_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetAuthdataCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    (VOS_VOID)TAF_APS_SndSetAuthDataInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/* Add by w00199382 for V7����ͬ��, 2012-04-07, Begin   */
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiGetLtecsCnfExpired_PreProc
 ��������  : ����L4A��Ϣ������ʱ����ʱԤ������
             (TI_TAF_APS_WAIT_GET_LTE_CS_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : w00182550
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiGetLtecsCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_GET_LTE_CS_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiGetLtecsCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndGetLtecsInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_LTE_CS_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiGetCemodeCnfExpired_PreProc
 ��������  : ����L4A��Ϣ������ʱ����ʱԤ������
             (TI_TAF_APS_WAIT_GET_CEMODE_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiGetCemodeCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_GET_CEMODE_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiGetCemodeCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndGetCemodeInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_CEMODE_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiSetPdprofInfoExpired_PreProc
 ��������  : ����L4A��Ϣ������ʱ����ʱԤ������
             (TI_TAF_APS_WAIT_SET_PDPROF_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��03��22��
    ��    ��   : x00126983
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetPdprofInfoExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_PDPROF_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetPdprofInfoExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndSetPdprofInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_PDPROF_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}


/* Add by w00199382 for V7����ͬ��, 2012-04-07, End   */

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiSetCgcontrdpCnfExpired_PreProc
 ��������  : ����L4A��Ϣ������ʱ����ʱԤ������
             (TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgcontrdpCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl = {0};
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgcontrdpCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    (VOS_VOID)TAF_APS_SndGetDynamicPrimPdpCtxInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT, 0);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiSetCgscontrdpCnfExpired_PreProc
 ��������  : ����L4A��Ϣ������ʱ����ʱԤ������
             (TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
  2.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ���ӻ�������л�ȡ��Ϣ

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgscontrdpCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl = {0};
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgscontrdpCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndGetDynamicSecPdpCtxInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT, 0);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiSetCgtftrdpCnfExpired_PreProc
 ��������  : ����L4A��Ϣ������ʱ����ʱԤ������
             (TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgtftrdpCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl = {0};
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgtftrdpCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    (VOS_VOID)TAF_APS_SndGetDynamicTftInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT, 0);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiSetCgeqosrdpCnfExpired_PreProc
 ��������  : ����L4A��Ϣ������ʱ����ʱԤ������
             (TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
  2.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ���ӻ�������л�ȡ��Ϣ

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiSetCgeqosrdpCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgeqosrdpCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndGetCgeqosrdpCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_TransL4aErrorCode
 ��������  : ת��L4A���صĴ�����
 �������  : VOS_UINT32         ulL4aErrCode
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��19��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_TransL4aErrorCode(
    VOS_UINT32                          ulL4aErrCode
)
{
    /* ���зǳɹ��Ĵ���������ز������ô��� */
    if (0 == ulL4aErrCode)
    {
        return TAF_PS_CAUSE_SUCCESS;
    }
    else
    {
        return TAF_PS_CAUSE_INVALID_PARAMETER;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmPdpSetupCnf_PreProc
 ��������  : �յ�ESM ID_APP_ESM_PDP_SETUP_CNF��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2015��12��7��
   ��    ��  : w00316404
   �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmPdpSetupCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_SETUP_CNF_STRU         *pstCnf;

    pstCnf = (APP_ESM_PDP_SETUP_CNF_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid((VOS_UINT8)pstCnf->ulCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmNdisconnCnf_PreProc
 ��������  : �յ�ESM ID_APP_ESM_NDISCONN_CNF��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2015��12��7��
   ��    ��  : w00316404
   �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmNdisconnCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_NDISCONN_CNF_STRU          *pstCnf;

    pstCnf = (APP_ESM_NDISCONN_CNF_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid((VOS_UINT8)pstCnf->ulCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmApsPdpNanageInd_PreProc
 ��������  : �յ�ESM ID_APP_ESM_PDP_MANAGER_IND��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���

 2.��    ��   : 2013��07��08��
   ��    ��   : Y00213812
   �޸�����   : VoLTE_PhaseI ��Ŀ������MODULE ID

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmApsPdpNanageInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_MANAGER_IND_STRU       *pstPdpManageInd;
    VOS_UINT8                           ucPdpId;
    TAF_CTRL_STRU                       stCtrl;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));
    /* MODULE IDĬ������ΪAT, �����Ҫ�ϱ���IMSA�Ļ�����������ϱ�
       SM_ESM_EPS_BEARER_INFO_IND_STRU��Ϣ������ˢ�� */
    stCtrl.ulModuleId   = WUEPS_PID_AT;
    stCtrl.usClientId   = TAF_APS_INVALID_CLIENTID;
    stCtrl.ucOpId       = TAF_APS_INVALID_OPID;

    pstPdpManageInd = (APP_ESM_PDP_MANAGER_IND_STRU*)pstMsg;

    /* ����(PdP Id) */
    if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&stCtrl,
                                                       (VOS_UINT8)pstPdpManageInd->ulCid,
                                                       &ucPdpId))
    {
        /* ���䲻��ʵ�壬��ӡ�쳣����ʱ��Ӧ�÷��䲻��ʵ�� */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEsmApsPdpNanageInd_PreProc, alloc pdp id fail");
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmApsPdpModifyCnf_PreProc
 ��������  : �յ�L4a ID_APP_ESM_PDP_MODIFY_CNF��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2015��12��7��
   ��    ��  : w00316404
   �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmApsPdpModifyCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_MODIFY_CNF_STRU      *pstPdpModifyCnf;

    pstPdpModifyCnf = (APP_ESM_PDP_MODIFY_CNF_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid((VOS_UINT8)pstPdpModifyCnf->ulCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmApsPdpModifyInd_PreProc
 ��������  : �յ�ESM ID_APP_ESM_PDP_MODIFY_IND��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2015��12��7��
   ��    ��  : w00316404
   �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmApsPdpModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_MODIFY_IND_STRU      *pstPdpModifyInd;

    pstPdpModifyInd = (APP_ESM_PDP_MODIFY_IND_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid((VOS_UINT8)pstPdpModifyInd->ulCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmApsPdpReleaseCnf_PreProc
 ��������  : �յ�ESM ID_APP_ESM_PDP_RELEASE_CNF��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2015��12��7��
   ��    ��  : w00316404
   �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmApsPdpReleaseCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_RELEASE_CNF_STRU       *pstPdpReleaseCnf;

    pstPdpReleaseCnf = (APP_ESM_PDP_RELEASE_CNF_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid((VOS_UINT8)pstPdpReleaseCnf->ulCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmApsPdpDeactivateInd_PreProc
 ��������  : �յ�ESM ID_APP_ESM_PDP_RELEASE_IND��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���

 2.��    ��  : 2015��5��29��
   ��    ��  : a00165503
   �޸�����  :  MODIFY for DTS2015051204781

 3.��    ��   : 2015��12��7��
   ��    ��   : w00316404
   �޸�����   : Split L4A Project
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmApsPdpDeactivateInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_RELEASE_IND_STRU       *pstPdpDeactInd;
    VOS_UINT8                           ucPdpId;

    pstPdpDeactInd = (APP_ESM_PDP_RELEASE_IND_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (VOS_TRUE == pstPdpDeactInd->bitOpLinkCid)
    {
        ucPdpId = TAF_APS_GetPdpIdByCid((VOS_UINT8)pstPdpDeactInd->ulCid);
    }
    else
    {
        ucPdpId = TAF_APS_GetPdpIdByEpsbId(pstPdpDeactInd->ulEpsbId);
    }

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmApsPdpSetupInd_PreProc
 ��������  : �յ�ID_APP_ESM_PDP_SETUP_IND��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��19��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��12��7��
    ��    ��   : w00316404
    �޸�����   : Split L4A Project

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmApsPdpSetupInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APP_ESM_PDP_SETUP_IND_STRU         *pstPdpSetupInd;
    VOS_UINT8                           ucPdpId;

    pstPdpSetupInd = (APP_ESM_PDP_SETUP_IND_STRU*)pstMsg;

    if (VOS_TRUE == pstPdpSetupInd->bitOpLinkCid)
    {
        /* ����Ϣ��������Cid�����Ҷ�Ӧ��PDP ID */
        ucPdpId = TAF_APS_GetPdpIdByCid((VOS_UINT8)(pstPdpSetupInd->ulCid));
    }
    else
    {
        /* ����Ϣ��������RabId�����Ҷ�Ӧ��PDP ID */
        ucPdpId = TAF_APS_GetPdpIdByEpsbId(pstPdpSetupInd->ulRabId);
    }

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmEpsBearInfoInd_PreProc
 ��������  : �յ�Esm SM_ESM_EPS_BEARER_INFO_IND_STRU�����Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
  1.��    ��  : 2011��12��22��
    ��    ��  : h44270
    �޸�����  : �����ɺ���

  2.��    ��   : 2012��4��16��
    ��    ��   : A00165503
    �޸�����   : DTS2012040100697: �Զ�Ӧ��ģʽ��, ���ཨ����ESP����, �û���
                 ���޸ĺ�ȥ����

  3.��    ��  : 2015��5��29��
    ��    ��  : a00165503
    �޸�����  :  MODIFY for DTS2015051204781
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmEpsBearInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
    TAF_CTRL_STRU                       stCtrl;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));
    /* MODULE IDĬ������ΪAT, �����Ҫ�ϱ���IMSA�Ļ�����������ϱ�
       SM_ESM_EPS_BEARER_INFO_IND_STRU��Ϣ������ˢ�� */
    stCtrl.ulModuleId   = WUEPS_PID_AT;
    stCtrl.usClientId   = TAF_APS_INVALID_CLIENTID;
    stCtrl.ucOpId       = TAF_APS_INVALID_OPID;
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

    pstBearerInfo = (SM_ESM_EPS_BEARER_INFO_IND_STRU*)pstMsg;


    ucCid = TAF_APS_GetCidFromLteBitCid(pstBearerInfo->ulBitCid);

    /* Cid��ֵ��Ч����ֱ�ӷ��� */
    if ( TAF_INVALID_CID == ucCid )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEsmEpsBearInfoInd_PreProc, invalid Cid");
        return VOS_TRUE;
    }

    /* ��������£�����CID������Pdp Id */
    if (SM_ESM_PDP_OPT_ACTIVATE == pstBearerInfo->enPdpOption)
    {
        ucPdpId = TAF_APS_GetPdpIdByCid(ucCid);
    }
    else
    {
        ucPdpId = TAF_APS_GetPdpIdByEpsbId(pstBearerInfo->ulEpsbId);
    }

    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEsmEpsBearInfoInd_PreProc, invalid Cid");
        return VOS_FALSE;
    }
    else
    {
        /* �Զ�Ӧ��ģʽ��, ��Ҫ�����µ�APSʵ�����洢������Ϣ */
        TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEsmEpsBearInfoInd_PreProc, Get PDP ID fail.");
    }


    /* cidΪ0ʱ����ʾ��Ĭ�ϳ��أ���ʱ����Ǽ�������һ���µ�PDP ID
       client id��op id��ʱ��Ϊ����Чֵ��������������ʱ���ٽ���ˢ��
    */
    if ( ((TAF_APS_DEFAULT_CID == ucCid) || (ucCid > APS_PDP_MAX_CID))
      && (SM_ESM_PDP_OPT_ACTIVATE == pstBearerInfo->enPdpOption) )
    {
        /* ����(PdP Id) */
        if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&stCtrl,
                                                           ucCid,
                                                           &ucPdpId))
        {
            /* ���䲻��ʵ�壬��ӡ�쳣����ʱ��Ӧ�÷��䲻��ʵ�� */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEsmEpsBearInfoInd_PreProc, alloc pdp id fail");
            return VOS_TRUE;
        }

        /* ��¼Ĭ�ϳ��صı�־ */
        if (TAF_APS_DEFAULT_CID == ucCid)
        {
           TAF_APS_SetPdpEntAttachBearerFlag(ucPdpId, VOS_TRUE);
        }
    }
    else
    {
        /* �쳣��Ϣ, ���� */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEsmEpsBearInfoInd_PreProc, Abnormal EPS Bearer.");
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmNotificationInd_PreProc
 ��������  : ID_EMS_APS_NOTIFICATION_IND������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��18��
    ��    ��   : Y00213812
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEsmNotificationInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    ESM_APS_NOTIFICATION_IND_STRU      *pstEsmNotiInd;

    pstEsmNotiInd = (ESM_APS_NOTIFICATION_IND_STRU*)pstMsg;

    /* ������Ϣ */
    TAF_APS_SndImsaSrvccCancelNotify(pstEsmNotiInd->enNotificationIndicator);

    return VOS_TRUE;
}

#endif

#endif

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSndcpActivateRsp_PreProc
 ��������  : �յ�Sndcp APS_SN_ACT_RSP_MSG_TYPE��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_SNDCP_ACTIVATE_RSP_MSG         *pstSnActRsp;

    pstSnActRsp = (APS_SNDCP_ACTIVATE_RSP_MSG*)pstMsg;

    /* ��SNDCP����Ϣ�л�ȡNSAPI,�����ȡ�������� */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByNsapi(pstSnActRsp->ApsSnActRsp.ucNsapi))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSndcpModifyRsp_PreProc
 ��������  : �յ�Sndcp APS_SN_MDF_RSP_MSG_TYPE��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpModifyRsp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_SNDCP_MODIFY_RSP_MSG           *pstSnModifyRsp;

    pstSnModifyRsp = (APS_SNDCP_MODIFY_RSP_MSG*)pstMsg;

    /* ��SNDCP����Ϣ�л�ȡNSAPI,�����ȡ�������� */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByNsapi(pstSnModifyRsp->ApsSnMdfRsp.ucNsapi))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSndcpDeactRsp_PreProc
 ��������  : �յ�Sndcp APS_SN_DEACT_RSP_MSG_TYPE��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
 1.��    ��  : 2011��12��22��
   ��    ��  : h44270
   �޸�����  : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSndcpDeactRsp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_SNDCP_DEACTIVATE_RSP_MSG           *pstSnDeactRsp;

    pstSnDeactRsp = (APS_SNDCP_DEACTIVATE_RSP_MSG*)pstMsg;

    /* ��SNDCP����Ϣ�л�ȡNSAPI,�����ȡ�������� */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByNsapi(pstSnDeactRsp->ApsSnDeActRsp.ucNsapi))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvNdIpv6ParaInfoNotifyInd_PreProc
 ��������  : �յ�NDCLINET��ID_NDCLIENT_APS_PARA_INFO_NOTIFY��Ϣ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��1��2��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��6��30��
    ��    ��   : A00165503
    �޸�����   : DTS2012062900707: IPv6���ųɹ�, Ӧ�û�ȡIPv6��ַǰ׺�쳣
  3.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  4.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ������PID��¼��ʵ��
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvNdIpv6ParaInfoNotifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_CTRL_STRU                       stCtrl;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType;
    NDCLIENT_APS_PARA_INFO_NOTIFY_STRU *pstNdIpv6ParaInfoNotifyInd;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_APS_STA_ENUM_UINT32             enState;


    PS_MEM_SET(&stCtrl, 0x00, sizeof(stCtrl));

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstNdIpv6ParaInfoNotifyInd = (NDCLIENT_APS_PARA_INFO_NOTIFY_STRU*)pstMsg;

    /* ��ȡNSAPI��Ӧ��APSʵ������ */
    ucPdpId = TAF_APS_GetPdpIdByNsapi(pstNdIpv6ParaInfoNotifyInd->ucRabId);

    enState = TAF_APS_GetPdpIdMainFsmState(ucPdpId);

    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        /* ����APSʵ���RA������Ϣ */
        pstPdpEntity->bitOpIpv6RaInfo = VOS_TRUE;
        PS_MEM_CPY((VOS_CHAR*)&pstPdpEntity->stIpv6RaInfo,
                   (VOS_CHAR*)&pstNdIpv6ParaInfoNotifyInd->stIpv6Info,
                   sizeof(NDCLIENT_APS_IPV6_INFO_STRU));

#if (FEATURE_ON == FEATURE_LTE)
        /* ͬ��RA��Ϣ��ESM */
        (VOS_VOID)TAF_APS_SndL4aIpv6InfoNotifyInd(pstPdpEntity->ucNsapi,
                                        &pstPdpEntity->stIpv6RaInfo);
#endif

        /* ��鵱ǰ���뼼��, �����GUģ, ��Ҫ����IPF */
        enRatType = TAF_APS_GetCurrPdpEntityRatType();

        if ( (TAF_APS_RAT_TYPE_GSM   == enRatType)
          || (TAF_APS_RAT_TYPE_WCDMA == enRatType) )
        {
            TAF_APS_IpfConfigUlFilter(ucPdpId);
        }

        /* ����Ѿ��յ�DHCP�Ļظ���Ϣ�������ϱ�����������NDCLIENT��־λ */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if ((TAF_APS_RAT_TYPE_1X    == enRatType)
         || (TAF_APS_RAT_TYPE_HRPD  == enRatType)
         || (TAF_APS_RAT_TYPE_EHRPD == enRatType))
        {
            TAF_APS_IpfConfigUlFilter(ucPdpId);

            if (TAF_APS_RAT_TYPE_EHRPD == enRatType)
            {
                /* ֪ͨEHSMˢ��IPV6��ַ */
                TAF_APS_SndEhsmPdnCtxInfoNotify(ucPdpId, EHSM_APS_PDN_OPTION_MODIFIED);
            }

            if (VOS_TRUE == pstPdpEntity->ucRcvDhcpDnsFlgIpv6)
            {

                /* ����Ѿ��ϱ����־λ */
                pstPdpEntity->ucRcvNdClientNtyFlg = VOS_FALSE;
                pstPdpEntity->ucRcvDhcpDnsFlgIpv4 = VOS_FALSE;
                pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_FALSE;
            }
            else
            {
                pstPdpEntity->ucRcvNdClientNtyFlg = VOS_TRUE;

                return VOS_TRUE;
            }

        }
#endif

        /* ��鵱ǰAPS�Ƿ����û�ʹ��, ������û�ʹ��, �ϱ�RA��Ϣ�¼� */
        if ((TAF_APS_INVALID_CLIENTID != TAF_APS_GetPdpEntClientId(ucPdpId, pstPdpEntity->stClientInfo.ucCid))
         && (VOS_TRUE == pstPdpEntity->ulUsedFlg)
         && ((TAF_APS_STA_ACTIVE == enState) || (TAF_APS_STA_MS_MODIFYING == enState)))
        {
            /* ��дAPP����ͷ */
            TAF_APS_SetPsCallEvtCtrl(ucPdpId, pstPdpEntity->stClientInfo.ucCid, &stCtrl);

            /* �ϱ�ID_EVT_TAF_PS_IPV6_INFO_IND�¼� */
            TAF_APS_SndIpv6RaInfoNotifyInd(&stCtrl,
                                           pstPdpEntity->stClientInfo.ucCid,
                                           pstPdpEntity->ucNsapi,
                                           (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);
        }
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvNdIpv6ParaInfoNotifyInd_PreProc: Can't find PDP ID form RAB ID!");
    }

    return VOS_TRUE;
}

#endif

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGetGprsActiveTypeReq_PreProc
 ��������  : ��ȡPPP����CID��Ӧ��PDP����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ    :
   1.��    ��  : 2011��12��22��
     ��    ��  : A00165503
     �޸�����  : �����ɺ���

  2.��    ��   : 2014��1��13��
    ��    ��   : A00165503
    �޸�����   : DTS2013122609183: L2P���������Ż�, ֱ�Ӹ���CID�������ж���
                 ��PDP���;���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGetGprsActiveTypeReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                              ulErrCode;
    TAF_PDP_TYPE_ENUM_UINT8                 enPdpType;
    TAF_CID_GPRS_ACTIVE_TYPE_STRU           stCidGprsActiveType;
    TAF_PS_MSG_STRU                        *pstAppMsg;
    TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU *pstGetGprsActiveTypeReq;

    /* ��ʼ�� */
    ulErrCode               = TAF_PARA_OK;
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstGetGprsActiveTypeReq = (TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU*)(pstAppMsg->aucContent);

    /* ��ȡGPRS�������� */
    PS_MEM_SET(&stCidGprsActiveType, 0x00, sizeof(TAF_CID_GPRS_ACTIVE_TYPE_STRU));
    stCidGprsActiveType.ucCid = pstGetGprsActiveTypeReq->stAtdPara.ucCid;

    enPdpType = Taf_GetCidType(pstGetGprsActiveTypeReq->stAtdPara.ucCid);

    /* ɾ��L2PЭ�����͵��жϴ��� */

    /* ֱ�Ӹ���CID�����ĵ�PDP���;�������PPPʵ������ */
    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            /* IP����,����IP���TE��������PPP��MT������PPP */
            stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
        case TAF_PDP_IPV4V6:
            /* IP����,����IP���TE��������PPP��MT������PPP */
            stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE;
            break;
#endif

        case TAF_PDP_PPP:
            /* PPP����,����PPP���TE��������PPP��MT�в�����PPP */
            stCidGprsActiveType.enActiveType = TAF_PPP_ACTIVE_TE_PPP_MT_NOT_PPP_TYPE;
            break;

        default:
            ulErrCode = TAF_PS_CAUSE_INVALID_PARAMETER;
            break;
    }

    (VOS_VOID)TAF_APS_SndGetGprsActiveTypeCnf(&(pstGetGprsActiveTypeReq->stCtrl),
                                   ulErrCode,
                                   &stCidGprsActiveType);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetDnsQueryReq_PreProc
 ��������  : ��ѯָ����PDP�����������Э�̵���DNS����DNS��Ϣ��Ԥ������
             (ID_MSG_TAF_PS_GET_NEGOTIATION_DNS_REQ)
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��20��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��10��17��
    ��    ��   : l00198894
    �޸�����   : DTS2012101606439, ����DNSĬ��ֵ�ظ�
  3.��    ��   : 2013��07��08��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseI ��Ŀ���ṹ�滻

  4.��    ��   : 2015��4��20��
    ��    ��   : Y00213812
    �޸�����   : ����CDMAģʽ����Ҫ����dormant״̬��discing״̬
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetDnsQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                        *pstPsMsg        = VOS_NULL_PTR;
    TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU    *pstNegoDnsReq   = VOS_NULL_PTR;
    TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU     stNegoDnsCnf;
    VOS_UINT8                               ucPdpId         = TAF_APS_INVALID_PDPID;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity    = VOS_NULL_PTR;
    TAF_APS_STA_ENUM_UINT32                 enStaState      = TAF_APS_STA_BUTT;
    TAF_APS_CDATA_PS_STATE_ENUM_UINT8       enCdataPsState;

    /* ��ʼ�� */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstNegoDnsReq   = (TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU *)pstPsMsg->aucContent;
    ucPdpId         = TAF_APS_GetPdpIdByCid(pstNegoDnsReq->ucCid);
    PS_MEM_SET(&stNegoDnsCnf, 0, sizeof(stNegoDnsCnf));

    /* ��д��Ϣ���� */
    /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
    stNegoDnsCnf.stCtrl                 = pstNegoDnsReq->stCtrl;
    /* Added by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

    stNegoDnsCnf.enCause                = TAF_PS_CAUSE_UNKNOWN;

    /* ��ȡCID��Ӧ��PdpId */
    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        enCdataPsState = TAF_APS_GetPdpEntCdataPsState(ucPdpId);

        /* ����CID��ӦPDP�Ƿ񼤻� */
        enStaState  = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
        if ( (TAF_APS_STA_ACTIVE            == enStaState)
          || (TAF_APS_STA_MS_MODIFYING      == enStaState)
          || (TAF_APS_STA_MS_DEACTIVATING   == enStaState)
          || (TAF_APS_STA_CDATA_DISCING     == enStaState)
          || (TAF_APS_CDATA_PS_STATE_ACTIVE == enCdataPsState) )
        {
            /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
            pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

            /* ��ȡ�ü���PDP��Ӧ����DNS, ��DNS��Ϣ */
            stNegoDnsCnf.stNegotiationDns.ucCid = pstNegoDnsReq->ucCid;
            stNegoDnsCnf.enCause = TAF_PS_CAUSE_SUCCESS;
            stNegoDnsCnf.stNegotiationDns.stDnsInfo.bitOpPrimDnsAddr = VOS_TRUE;
            stNegoDnsCnf.stNegotiationDns.stDnsInfo.bitOpSecDnsAddr  = VOS_TRUE;

            if (VOS_TRUE == pstPdpEntity->PdpDnsFlag)
            {
                if (VOS_TRUE == pstPdpEntity->PdpDns.OP_PriDns)
                {
                    PS_MEM_CPY(stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucPrimDnsAddr,
                               pstPdpEntity->PdpDns.aucPriDns,
                               TAF_IPV4_ADDR_LEN);
                }

                if (VOS_TRUE == pstPdpEntity->PdpDns.OP_SecDns)
                {
                    PS_MEM_CPY(stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucSecDnsAddr,
                               pstPdpEntity->PdpDns.aucSecDns,
                               TAF_IPV4_ADDR_LEN);
                }
            }
        }
    }

    /* ������������ATģ�� */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_NEGOTIATION_DNS_CNF,
                     &stNegoDnsCnf,
                     sizeof(TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU));

    return VOS_TRUE;
}





/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiApsLimitPdpActExpired_PreProc
 ��������  : ��ͣPDP���ʱ����ʱԤ������(AT&T DCM���ƣ�PDP��������
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��16��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiApsLimitPdpActExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiApsMsActvaingExpired_PreProc
 ��������  : APS�����PDP���ʱԤ������(AT&T DCM���ƣ�PDP��������
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��16��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiApsMsActvaingExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* PDP�������޴���:�˶�ʱ����ʱ��Ϊ�쳣,PDP���������һ�δ��� */
    TAF_APS_ProcPdpActLimit_PreProc(1);

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetActPdpLimitTimerLen
 ��������  : ������ͣPDP���ʱ����ʱ��(AT&T DCM���ƣ�PDP��������
 �������  : VOS_UINT8 ucFailCount
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��16��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_GetActPdpLimitTimerLen(
    VOS_UINT8                           ucFailCount
)
{
    VOS_UINT32                          ulTimeLen;

    ulTimeLen = 0;

    /* ��ͣPDP���ʱ��ʱ�����ż���ʧ�ܵĴ�����ȷ����С�ڵ���10��ֱ�ӷ���ʱ��0.
    11-18�ΰ���10s��������ʱ��������18�ε�ͳһʹ��90sʱ�� */
    if (ucFailCount <= TAF_APS_PDP_ACT_LIMIT_NO_DELAY_COUNT_THRESHOLD)
    {
        return 0;
    }

    /* PDP�����11-19��֮�ڣ�����10s��������������ʱ�� */
    if (ucFailCount < TAF_APS_PDP_ACT_LIMIT_STEP_DELAY_COUNT_THRESHOLD)
    {
        ulTimeLen = (ucFailCount - TAF_APS_PDP_ACT_LIMIT_NO_DELAY_COUNT_THRESHOLD)
                        * TAF_APS_PDP_ACT_LIMIT_STEP_TIME;
    }
    else
    {   /* PDP�����19��(����19��)���ϣ�����90sʱ��������ʱ�� */
        /* ��ʧ�ܴ�����10��������ʱ��PDP��ͣ���ʱ��ʹ�����ʱ�� */
        if (0 == (ucFailCount % TAF_APS_PDP_ACT_LIMIT_RANDOM_TIME_FAILCOUNT))
        {
            ulTimeLen = TAF_APS_PDP_ACT_LIMIT_AVERAGE_DELAY_TIME
                        + VOS_Rand(TAF_APS_PDP_ACT_LIMIT_RANDOM_TIME_THRESHOLD);
        }
        else
        {
            ulTimeLen = TAF_APS_PDP_ACT_LIMIT_AVERAGE_DELAY_TIME;
        }
    }

    /* ��ʱ��ʱ����λΪms */
    return (ulTimeLen * TIMER_S_TO_MS_1000);
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ProcPdpActLimit_PreProc
 ��������  : �յ�����ܡ�����ȥ������߼��ʱ������������
 �������  : VOS_UINT8 ucTryingCount
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��15��
    ��    ��   : M00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_ProcPdpActLimit_PreProc(VOS_UINT8 ucTryingCount)
{
    TAF_APS_PDP_ACT_LIMIT_INFO_STRU    *pstPdpActLimitInfo;

    pstPdpActLimitInfo = TAF_APS_GetPdpActLimitInfoAddr();

    /* �ж�PDP�������޹����Ƿ�� */
    if (VOS_TRUE == pstPdpActLimitInfo->ucPdpActLimitFlg)
    {
        pstPdpActLimitInfo->ucPdpActFailCount = pstPdpActLimitInfo->ucPdpActFailCount + ucTryingCount;

        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID))
        {
            return;
        }

        if (pstPdpActLimitInfo->ucPdpActFailCount > TAF_APS_PDP_ACT_LIMIT_NO_DELAY_COUNT_THRESHOLD)
        {
            TAF_APS_StartTimer(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_GetActPdpLimitTimerLen(pstPdpActLimitInfo->ucPdpActFailCount), TAF_APS_PDP_ACT_LIMIT_PDP_ID);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_IsPdpActLimit_PreProc
 ��������  : �ж��ǲ���PDP��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��30��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_IsPdpActLimit_PreProc(VOS_VOID)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    enCurrRatType        = TAF_APS_GetCurrPdpEntityRatType();

    /* PS����Ч����״̬���д��� */
    if (VOS_FALSE == TAF_APS_GetCurrPdpEntitySimRegStatus())
    {
        return VOS_FALSE;
    }

    /* ĿǰPDP�������޵Ĺ���ֻ������GUģ */
    if ((TAF_APS_RAT_TYPE_GSM == enCurrRatType)
     || (TAF_APS_RAT_TYPE_WCDMA == enCurrRatType))
    {
        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetPdpContextStateReq_PdpActLimit_PreProc
 ��������  : �յ�ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��PDP�������޵�Ԥ��
             ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��4��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��22��
    ��    ��   : Y00213812
    �޸�����   : �޸�PS��������ϱ�
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_PdpActLimit_PreProc(
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq
)
{
    if (VOS_TRUE == TAF_APS_IsPdpActLimit_PreProc())
    {
        /* ������ȥ���� */
        if (TAF_CGACT_ACT != pstSetPdpStateReq->stCidListStateInfo.ucState)
        {
            return VOS_FALSE;
        }

        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                    TAF_PS_CAUSE_PDP_ACTIVATE_LIMIT);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvOmSetDsflowRptReq_PreProc
 ��������  : �յ�ID_NAS_OM_SET_DSFLOW_RPT_REQ������OM�����ϱ���Ϣ
 �������  : ulEventType        -- �¼�����
             pstMsg             -- ��Ϣ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��09��
    ��    ��   : l00198894
    �޸�����   : Probe·�⹤�߶Խ���Ŀ��������

  2.��    ��   : 2015��7��09��
    ��    ��   : wx270776
    �޸�����   : OM�ں�

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvOmSetDsflowRptReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by wx270776 for OM�ں�, 2015-7-1, begin */
    NAS_OM_SET_DSFLOW_RPT_REQ_STRU     *pstDsflowRptReq = VOS_NULL_PTR;
    NAS_OM_SET_DSFLOW_RPT_CNF_STRU     *pstDsflowRptCnf = VOS_NULL_PTR;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx = VOS_NULL_PTR;//global
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulRet;

    /* ������Ϣ */
    ulMsgLen        = sizeof(NAS_OM_SET_DSFLOW_RPT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstDsflowRptCnf = (NAS_OM_SET_DSFLOW_RPT_CNF_STRU*)PS_ALLOC_MSG(WUEPS_PID_TAF, ulMsgLen);
    if (VOS_NULL_PTR == pstDsflowRptCnf)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvOmSetDsflowRptReq_PreProc: PS_MEM_ALLOC Failed!");

        return VOS_FALSE;
    }

    /* ��ʼ�� */
    PS_MEM_SET((VOS_UINT8*)pstDsflowRptCnf + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLen);

    pstDsflowRptReq = (NAS_OM_SET_DSFLOW_RPT_REQ_STRU*)pstMsg;

    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* ����OM�����ϱ���־λ */
    switch(pstDsflowRptReq->enRptAction)
    {
        case NAS_OM_REPORT_START:
            if ( (pstDsflowRptReq->usRptPeriod >= TI_TAF_APS_DSFLOW_REPORT_LEN)
              && (0 == (pstDsflowRptReq->usRptPeriod % TI_TAF_APS_DSFLOW_REPORT_LEN)) )
            {
                pstApsDsFlowCtx->ucDsFlowOMReportFlg    = VOS_TRUE;
                pstApsDsFlowCtx->ucDsFlowOMRptPeriod    = (VOS_UINT8)(pstDsflowRptReq->usRptPeriod / TI_TAF_APS_DSFLOW_REPORT_LEN);
                pstDsflowRptCnf->enResult                 = NAS_OM_RESULT_NO_ERROR;
            }
            else
            {
                pstDsflowRptCnf->enResult                 = NAS_OM_RESULT_INCORRECT_PARAMETERS;
            }
            break;
        case NAS_OM_REPORT_STOP:
            pstApsDsFlowCtx->ucDsFlowOMReportFlg        = VOS_FALSE;
            pstApsDsFlowCtx->ucDsFlowOMRptPeriod        = 0;
            break;
        default:
            pstDsflowRptCnf->enResult                     = NAS_OM_RESULT_INCORRECT_PARAMETERS;
            break;
    }

    /* �����Ϣ���� */
    pstDsflowRptCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstDsflowRptCnf->ulMsgId          = ID_NAS_OM_SET_DSFLOW_RPT_CNF;
    pstDsflowRptCnf->usOriginalId     = pstDsflowRptReq->usOriginalId;
    pstDsflowRptCnf->usTerminalId     = pstDsflowRptReq->usTerminalId;
    pstDsflowRptCnf->ulTimeStamp      = pstDsflowRptReq->ulTimeStamp;
    pstDsflowRptCnf->ulSN             = pstDsflowRptReq->ulSN;


    /* ������Ϣ */
    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstDsflowRptCnf);
    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("NAS_MMC_SndOmOtaCnf:WARNING: Send msg fail.");

        return VOS_FALSE;
    }



    return VOS_TRUE;
    /* Modified by wx270776 for OM�ں�, 2015-7-1, end */

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvMmcServiceStatusInd_PreProc
 ��������  : �յ�ID_MMC_APS_SERVICE_STATUS_IND��Ԥ����
 �������  : ulEventType        -- �¼�����
             pstMsg             -- ��Ϣ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��30��
    ��    ��   : m00217266
    �޸�����   : ��������Ҫ���ڼ�¼ID_MMC_APS_SERVICE_STATUS_IND��Ϣ����֮ǰpdpʵ��Ľ��뼼��
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvMmcServiceStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*
        1��CDMA������ʱ��MMC���ٸ�CDS����Ϣ֪ͨ���뼼���л���ֻ֪ͨ��APS
        2��GULģʽ�£���APS֪ͨCDS���뼼�������ͬʱAPS 3GPP״̬����ģʽ���������߼����䣻
        3��CLģʽ�£�MMC�ϱ�NULL��APS��APS���ݵ�ǰ����ҵ�����ڵ�ģʽ�����Ƿ�֪ͨCDS
            1.LTE�£�APS֪ͨCDS���뼼��ΪNULL��APS�ڲ��Ĵ�����GUL����һ�£�
            2.DO�£�APS֪ͨCDS���뼼��ΪNULL��ֻ��Ԥ��������Ϣ��
            3.1X�£�APS���Ը���Ϣ����֪ͨCDS��
        4��CLģʽ�£�MMC�ϱ�LTE��APS��APS���ݵ�ǰ����ҵ�����ڵ�ģʽ������δ���
            1.LTE�£�APS֪ͨCDS���뼼��ΪLTE��APS�ڲ��Ĵ�����GUL����һ�£�
            2.DO�£�APS���Ը���Ϣ�������ȴ�MMA�ķ���״̬֪ͨ��Ȼ����֪ͨCDS��
            3.1X�£�APS���Ը���Ϣ�������ȴ�MMA�ķ���״̬֪ͨ��DORMANTֱ̬��֪ͨCDS��
              ACTIVE״̬��֪ͨ����ȥ������ɺ�������֪ͨCDS��ǰ�Ľ��뼼����
    */

    MMC_APS_SERVICE_STATUS_IND_STRU    *pstSerStaInd;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enLastRatType;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrDataServiceMode;
#endif

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSerStaInd  = (MMC_APS_SERVICE_STATUS_IND_STRU*)pstMsg;
    enRatType     = TAF_APS_ConvertMmcRatType(pstSerStaInd->enRatType);
    enLastRatType = TAF_APS_GetCurrPdpEntityRatType();

    /* ���µ�PS��״̬ */
    TAF_APS_SetCurrPdpEntitySimRegStatus(pstSerStaInd->ulPsSimRegStatus);

    if (TAF_APS_RAT_TYPE_NULL != enRatType)
    {
         /* ��¼���õ�PS��״̬���ڹ���ʱʹ�� */
        TAF_APS_SET_RAT_TYPE_IN_SUSPEND(enRatType);

    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    enCurrDataServiceMode = TAF_APS_GetCurrPdpEntityDataServiceMode();

    if (TAF_APS_RAT_TYPE_NULL != enRatType)
    {

        if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
        {
            /* ���ý��뼼�� */
            if (TAF_APS_RAT_TYPE_LTE == enCurrDataServiceMode)
            {
                TAF_APS_SetCurrPdpEntityRatType(enRatType);
            }

            /* ֪ͨCDS��ǰ���뼼���ı� */
            if (VOS_TRUE == TAF_APS_IsNeedNotifyCdsModeChange(enRatType, enCurrDataServiceMode))
            {
                TAF_APS_SndCdsModeChangeInd(enRatType);
            }
        }
        else
        {
            TAF_APS_SetCurrPdpEntityRatType(enRatType);
            TAF_APS_SndCdsModeChangeInd(enRatType);
        }
    }
    else
    {
        if (TAF_APS_RAT_TYPE_1X == enCurrDataServiceMode)
        {
            /* ���ԭ����1Xģʽ��������MMC�ϱ���NULL��֪ͨ */
            return VOS_TRUE;
        }
        else if ((TAF_APS_RAT_TYPE_HRPD  == enCurrDataServiceMode)
              || (TAF_APS_RAT_TYPE_EHRPD == enCurrDataServiceMode))
        {
            /* ֪ͨCDS��ǰ���뼼���ı�,����״̬������ */
            TAF_APS_SndCdsModeChangeInd(enRatType);

            return VOS_TRUE;
        }
        else
        {
            TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_NULL);
        }
    }

    TAF_APS_LogOldNewPdpRatType(TAF_APS_GetCurrPdpEntityRatType(), enLastRatType);

    /* CLģʽ�£�����ҵ���LTEģʽ������״̬������ */
    if ((VOS_TRUE == TAF_SDC_IsConfigCLMode())
     && (TAF_APS_RAT_TYPE_LTE != enCurrDataServiceMode))
    {
        return VOS_TRUE;
    }

#else

    /* �ϱ���ǰ�Ľ��뼼��ģʽ */
    TAF_APS_LogOldNewPdpRatType(enRatType, enLastRatType);

    TAF_APS_SetCurrPdpEntityRatType(enRatType);

#endif

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* �����ǰPDPʵ�岻ΪINACTIVE״̬�������ڲ���Ϣ��״̬������ */
        if (VOS_TRUE == TAF_APS_IsPdpIdValid(ucPdpId))
        {
            /* �ڲ���Ϣ��Я������MMC�ϱ��ķ���״̬���������������е�
               ״̬��������ڲ���Ϣʱ��ʹ����Ϣ��Я������Ϣ
            */
            (VOS_VOID)TAF_APS_SndInterServiceStatusChangeInd(ucPdpId,
                                                   enRatType,
                                                   enLastRatType,
                                                   pstSerStaInd->ulPsSimRegStatus,
                                                   VOS_FALSE,
                                                   TAF_APS_INTER_SERVICE_RESULT_LTE);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_Aps_RcvGetCidSdfReq
 ��������  : ���ڻ�ȡ����NV���е�SDF������ϢԤ����
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��09��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsGetCidSdfReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucNum;
    TAF_PS_SDF_INFO_REQ_STRU           *pstSdfInfoReq;
    TAF_PS_SDF_INFO_CNF_STRU           *pstSdfInfoCnf;

    pstSdfInfoReq = (TAF_PS_SDF_INFO_REQ_STRU *)pstMsg;

    /* ������Ϣ�ڴ� */
    pstSdfInfoCnf = (TAF_PS_SDF_INFO_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                            sizeof(TAF_PS_SDF_INFO_CNF_STRU));

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstSdfInfoCnf )
    {
        MN_ERR_LOG("TAF_APS_RcvPsGetCidSdfReq_PreProc:  ERROR : PS_MEM_ALLOC Error!");
        return VOS_TRUE;
    }

    PS_MEM_SET(pstSdfInfoCnf, 0, sizeof(TAF_PS_SDF_INFO_CNF_STRU));

    /* ��д��Ϣͷ */
    pstSdfInfoCnf->stCtrl = pstSdfInfoReq->stCtrl;

    for (ucNum = 1; ucNum <= TAF_MAX_CID_NV; ucNum++)
    {
        if (VOS_OK == TAF_APS_GetSdfParaInfo(ucNum,
                              &(pstSdfInfoCnf->stSdfInfo.astSdfPara[pstSdfInfoCnf->stSdfInfo.ulSdfNum])))
        {
            pstSdfInfoCnf->stSdfInfo.ulSdfNum ++;
        }
    }

    /* ����ID_MSG_TAF_GET_CID_SDF_CNF��Ϣ */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_CID_SDF_CNF,
                     (VOS_VOID *) pstSdfInfoCnf,
                     sizeof(TAF_PS_SDF_INFO_CNF_STRU));

    /* �ͷ����ڴ��SDF�������ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstSdfInfoCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSetImsPdpCfgReq_PreProc
 ��������  : ����PDP�Ƿ�֧��IMS
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��29��
    ��    ��   : z00301431
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSetImsPdpCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_CID_IMS_CFG_TBL_STRU       *pstCidImsCfgTbl;
    TAF_PS_SET_IMS_PDP_CFG_REQ_STRU    *pstSetImsPdpCfgReq;
    TAF_PS_SET_IMS_PDP_CFG_CNF_STRU     stSetImsPdpCfgCnf;
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucImsFlag;

    enCause             = TAF_PS_CAUSE_SUCCESS;
    pstSetImsPdpCfgReq  = (TAF_PS_SET_IMS_PDP_CFG_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);

    ucCid       = pstSetImsPdpCfgReq->stImsPdpCfg.ucCid;
    ucImsFlag   = pstSetImsPdpCfgReq->stImsPdpCfg.ucImsFlag;

    /* �ж�CID��Ч�� */
    if (!(TAF_PS_PDP_CONTEXT_CID_VALID(ucCid)))
    {
        enCause = TAF_PS_CAUSE_CID_INVALID;
    }
    else
    {
        /* ����CID��IMS���� */
        pstCidImsCfgTbl = TAF_APS_GetCidImsCfgTable();
        pstCidImsCfgTbl->aucImsFlag[ucCid] = ucImsFlag;
    }

    PS_MEM_SET(&stSetImsPdpCfgCnf, 0, sizeof(TAF_PS_SET_IMS_PDP_CFG_CNF_STRU));

    /* ��д��Ϣͷ */
    stSetImsPdpCfgCnf.stCtrl  = pstSetImsPdpCfgReq->stCtrl;
    stSetImsPdpCfgCnf.enCause = enCause;

    /* ����ID_EVT_TAF_PS_SET_IMS_PDP_CFG_CNF��Ϣ */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_IMS_PDP_CFG_CNF,
                               &stSetImsPdpCfgCnf,
                               sizeof(TAF_PS_SET_IMS_PDP_CFG_CNF_STRU));

    return VOS_TRUE;
}

/* Added by m00217266 for L-C��������Ŀ, 2014-2-12, begin */
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 �� �� ��  : TAF_APS_LC_Check_Req_Valid
 ��������  : ��LC������ģʽ�£�����������Ч��
 �������  : TAF_CTRL_STRU
 �������  : ��
 �� �� ֵ  : VOS_UINT8,
             0:��Ч����
             1:��Ч����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_APS_LCCheckReqValid(
    TAF_CTRL_STRU                       *pstCtrlInfo
)
{
    TAF_PH_MODE                         ucPhMode;

    ucPhMode                            = MMA_GetCurrPhMode();

    /* �ǿ���״̬���������� */
    if (TAF_PH_MODE_FULL != ucPhMode)
    {
        return VOS_TRUE;
    }
    /* ��L+C�����������£���CMMCA�·����������� */
    if ((VOS_TRUE        == TAF_SDC_IsConfigCLInterWorkCOutside())
     && (WUEPS_PID_CMMCA != pstCtrlInfo->ulModuleId))
    {
        return VOS_FALSE;
    }

    /* �ڷ�L+C�����������£�CMMCA�·����������� */
    if ((VOS_FALSE       == TAF_SDC_IsConfigCLInterWorkCOutside())
     && (WUEPS_PID_CMMCA == pstCtrlInfo->ulModuleId))
    {
        return VOS_FALSE;
    }


    return VOS_TRUE;
}
#endif
/* Added by m00217266 for L-C��������Ŀ, 2014-2-12, end */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccDataCallSuspendInd_PreProc
 ��������  : �յ�ID_XCC_APS_DATA_CALL_SUSPEND_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��18��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDataCallSuspendInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_SUSPEND_IND_STRU *pstSuspendInd = VOS_NULL_PTR;

    pstSuspendInd = (XCC_APS_DATA_CALL_SUSPEND_IND_STRU *)pstMsg;

    TAF_APS_SET_CDATA_SUSPEND_STATUS(TAF_APS_CDMA_TC_SUSPENDED);


    /* TO DO:����״̬���д������Ϣ */

    /* DMT����ʱ�����g_ulApsTestStubΪTRUE���򲻻ظ�SUSPEND_RSP��Ϣ */
    if (VOS_FALSE == g_ulApsTestStub)
    {
        TAF_APS_SndXccDataCallSuspendRsp(pstSuspendInd->ucConnectId);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccDataCallResumeInd_PreProc
 ��������  : �յ�ID_XCC_APS_DATA_CALL_RESUME_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��18��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDataCallResumeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_RESUME_IND_STRU  *pstResumeInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;
    VOS_UINT32                          ulExist1XService;
    VOS_UINT8                           ucPdpId;



    /* ��ȡ��Ϣ���� */
    pstResumeInd            = (XCC_APS_DATA_CALL_RESUME_IND_STRU *)pstMsg;
    ulExist1XService        = TAF_APS_Get1XPsServiceStatus();

    TAF_APS_SET_CDATA_SUSPEND_STATUS(TAF_APS_CDMA_TC_RESUMED);


    if ((TAF_APS_RAT_TYPE_NULL == TAF_APS_GetCurrPdpEntityRatType())
     && (VOS_TRUE == ulExist1XService))
    {
        if (VOS_FALSE == TAF_APS_GetClDelaySearch())
        {
            TAF_APS_LogOldNewPdpRatType(TAF_APS_RAT_TYPE_1X, TAF_APS_RAT_TYPE_NULL);

            TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_1X);
        }
    }

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->stCdataInfo.ucConnectId == pstResumeInd->ucConnectId)
        {
            /* ��ǰֻ֧��һ·���У�ConnectIdƥ��ɹ��󣬽���״̬������ */
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccOrigDataCallCnf_PreProc
 ��������  : �յ�ID_XCC_APS_ORIG_DATA_CALL_CNF��Ϣ�Ĵ���
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

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccOrigDataCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_ORIG_DATA_CALL_CNF_STRU    *pstOrigCallCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstOrigCallCnf = (XCC_APS_ORIG_DATA_CALL_CNF_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstOrigCallCnf->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccOrigDataCallCnf_PreProc:Wrong CallId", pstOrigCallCnf->ucCallId);
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccHangupDataCallCnf_PreProc
 ��������  : �յ�ID_XCC_APS_HANGUP_DATA_CALL_CNF��Ϣ�Ĵ���
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

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccHangupDataCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_HANGUP_DATA_CALL_CNF_STRU  *pstHangUpCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstHangUpCnf = (XCC_APS_HANGUP_DATA_CALL_CNF_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstHangUpCnf->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccHangupDataCallCnf_PreProc:Wrong CallId", pstHangUpCnf->ucCallId);
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccDataCallDiscInd_PreProc
 ��������  : �յ�ID_XCC_APS_DATA_CALL_DISC_IND��Ϣ�Ĵ���
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

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDataCallDiscInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscCallInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstDiscCallInd = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->stCdataInfo.ucConnectId == pstDiscCallInd->ucConnectId)
        {
            /* ��״̬������ */
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccIncomintCallInd_PreProc
 ��������  : �յ�ID_XCC_APS_INCOMING_CALL_IND��Ϣ�Ĵ���
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

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_INCOMING_CALL_IND_STRU     *pstIncomingCallInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstIncomingCallInd = (XCC_APS_INCOMING_CALL_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* ��ǰֻ֧��dormant״̬�£����緢���Ѱ���������Ч��PDP ID��ֱ������ */
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }



        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->stCdataInfo.enSo == pstIncomingCallInd->enSo)
        {
            /* ����ConnectId��APSʵ���� */
            TAF_APS_SetPdpEntConnectId(ucPdpId, pstIncomingCallInd->ucConnectId);

            TAF_APS_SndXccIncomingCallRsp(pstPdpEntity->stCdataInfo.ucCallId,
                                          pstIncomingCallInd->ucConnectId,
                                          XCC_APS_RESULT_SUCC);

            /* ��״̬������ */
            return VOS_FALSE;
        }
    }

    TAF_APS_SndXccIncomingCallRsp(pstIncomingCallInd->ucCallId,
                                  pstIncomingCallInd->ucConnectId,
                                  XCC_APS_RESULT_FAIL);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccDataCallConnInd_PreProc
 ��������  : �յ�ID_XCC_APS_DATA_CALL_CONN_IND��Ϣ�Ĵ���
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

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDataCallConnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_CONN_IND_STRU    *pstConnCallInd = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstConnCallInd = (XCC_APS_DATA_CALL_CONN_IND_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstConnCallInd->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccDataCallConnInd_PreProc:Wrong CallId", pstConnCallInd->ucCallId);
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccDataServiceConnInd_PreProc
 ��������  : �յ�ID_XCC_APS_DATA_SERVICE_CONNECT_IND��Ϣ�Ĵ���
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

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccDataServiceConnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_SERVICE_CONNECT_IND_STRU        *pstServiceConnInd = VOS_NULL_PTR;
    VOS_UINT8                                     ucPdpId;

    pstServiceConnInd = (XCC_APS_DATA_SERVICE_CONNECT_IND_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstServiceConnInd->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccDataServiceConnInd_PreProc:Wrong CallId", pstServiceConnInd->ucCallId);
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccAnswerDataCallCnf_PreProc
 ��������  : �յ�ID_XCC_APS_ANSWER_DATA_CALL_CNF��Ϣ�Ĵ���
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

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccAnswerDataCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_ANSWER_DATA_CALL_CNF_STRU  *pstAnswerCallCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstAnswerCallCnf = (XCC_APS_ANSWER_DATA_CALL_CNF_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstAnswerCallCnf->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccAnswerDataCallCnf_PreProc:Wrong CallId", pstAnswerCallCnf->ucCallId);
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccSetPdpEntDormantTimer_PreProc
 ��������  : SOCM��Ϣ����Dormant Timer
 �������  : XCC_APS_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsgInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��1��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��7��
    ��    ��   : g00261581
    �޸�����   : ����Dormant TIʱ�������PdpIdʵ���޹�
*****************************************************************************/
VOS_VOID TAF_APS_RcvXccSetPdpEntDormantTimer_PreProc(
    XCC_APS_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsgInd
)
{
    VOS_UINT8                           ucPdpId;

    switch (pstSoCtrlMsgInd->ucDormCntl)
    {
        case XCC_APS_SOCM_DORMANT_TIMER_CTRL_DISABLE:
            TAF_APS_SetSocmDormantTiLen(0);
            TAF_APS_SetUserCfgDormTiVal(0);
            break;

        case XCC_APS_SOCM_DORMANT_TIMER_CTRL_SET_MIN_VALUE:
        case XCC_APS_SOCM_DORMANT_TIMER_CTRL_SET_MIN_AND_CUR_VALUE:
            if (TAF_APS_GetSocmDormantTiLen() < (pstSoCtrlMsgInd->ucDormTimer * 100))
            {
                TAF_APS_SetSocmDormantTiLen(pstSoCtrlMsgInd->ucDormTimer * 100);
            }

            for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
            {
                if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
                {
                    continue;
                }

                if (pstSoCtrlMsgInd->enSo != TAF_APS_GetPdpEntSo(ucPdpId))
                {
                    continue;
                }

                if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
                {
                    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

                    if (TAF_APS_GetUserCfgDormTiVal() > TAF_APS_GetSocmDormantTiLen())
                    {
                        TAF_APS_StartTimer(TI_TAF_APS_CDATA_DORMANT, TAF_APS_GetUserCfgDormTiVal(), ucPdpId);
                    }
                    else
                    {
                        TAF_APS_StartTimer(TI_TAF_APS_CDATA_DORMANT, TAF_APS_GetSocmDormantTiLen(), ucPdpId);
                    }
                }
            }

            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvXccSetPdpEntDormantTimer_PreProc, Invalid DormCntl Field");
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccSetPacketZoneReconnFeature_PreProc
 ��������  : SOCM Msg used to config Packet Zone Reconnect Feature and Packet Zone Hysteresis Feature
             Parse SOCM Msg
 �������  : XCC_APS_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsgInd
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��23��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_RcvXccSetPacketZoneReconnFeature_PreProc(
    XCC_APS_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsgInd
)
{
    /* Parse Socm msg according to Pkt_Conect_Cntl Field */
    switch (pstSoCtrlMsgInd->ucPktConCntl)
    {
        case XCC_APS_SOCM_PACKET_ZONE_RECONNECT_CTRL_DISABLE:
            TAF_APS_EpdszidSocmDisableReconn();
            break;

        case XCC_APS_SOCM_PACKET_ZONE_RECONNECT_CTRL_ENABLE:
            TAF_APS_EpdszidSocmEnableReconn(pstSoCtrlMsgInd->ucPktZoneListLen);
            break;

        case XCC_APS_SOCM_PACKET_ZONE_RECONNECT_CTRL_CLEAR:
            TAF_APS_EpdszidSocmClearPacketZoneList(pstSoCtrlMsgInd->ucPktZoneListLen);
            break;

        case XCC_APS_SOCM_PACKET_ZONE_RECONNECT_CTRL_TRANSFER:
            TAF_APS_EpdszidScomTransferPzid(pstSoCtrlMsgInd);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccSoCntrlMsg_PreProc
 ��������  : �յ�ID_XCC_APS_SERVICE_OPTION_CONTROL_MESSAGE��Ϣ�Ĵ���
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

  2.��    ��   : 2015��1��7��
    ��    ��   : g00261581
    �޸�����   : ����Packet zone���Թ��ܵ�����
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXccSoCtrlMsg_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_SO_CTRL_MSG_IND_STRU       *pSoCtrlMsg;

    pSoCtrlMsg = (XCC_APS_SO_CTRL_MSG_IND_STRU *)pstMsg;

    switch (pSoCtrlMsg->enFieldType)
    {
        case XCC_APS_SO_CTRL_FIELD_DORMANT_TIMER_CTRL:
            TAF_APS_RcvXccSetPdpEntDormantTimer_PreProc(pSoCtrlMsg);
            break;

        case XCC_APS_SO_CTRL_FIELD_PACKET_ZONE_RECONN_CTRL:
            TAF_APS_RcvXccSetPacketZoneReconnFeature_PreProc(pSoCtrlMsg);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvXccSoCtrlMsg_PreProc, Error Socm msg");
            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppActCnf_PreProc
 ��������  : �յ�ID_PPP_APS_PDP_ACT_CNF��Ϣ�Ĵ���
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

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppActCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_ACT_CNF_STRU               *pstPppActCnf = VOS_NULL_PTR;

    pstPppActCnf = (PPP_APS_ACT_CNF_STRU *)pstMsg;

    if (TAF_APS_INVALID_PDPID != TAF_APS_GetPdpIdByPndId(pstPppActCnf->ucPdnId))
    {
        return VOS_FALSE;
    }

    /* ���򲻽�״̬������ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppDeactInd_PreProc
 ��������  : �յ�ID_PPP_APS_PDP_DEACT_CNF��Ϣ�Ĵ���
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

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_DEACT_CNF_STRU             *pstPppDeactCnf  = VOS_NULL_PTR;

    pstPppDeactCnf = (PPP_APS_DEACT_CNF_STRU *)pstMsg;

    if (TAF_APS_INVALID_PDPID != TAF_APS_GetPdpIdByPndId(pstPppDeactCnf->ucPdnId))
    {
        return VOS_FALSE;
    }

    /* ���򲻽�״̬������ */
    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppDeactNtf_PreProc
 ��������  : �յ�ID_PPP_APS_PDP_DEACT_IND��Ϣ�Ĵ���
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

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppDeactNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_DEACT_NTF_STRU             *pstPppDeactNtf = VOS_NULL_PTR;

    pstPppDeactNtf = (PPP_APS_DEACT_NTF_STRU *)pstMsg;

    if (TAF_APS_INVALID_PDPID != TAF_APS_GetPdpIdByPndId(pstPppDeactNtf->ucPdnId))
    {
        return VOS_FALSE;
    }

    /* ���򲻽�״̬������ */
    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppModifyInd_PreProc
 ��������  : �յ�ID_PPP_APS_MODIFY_IND��Ϣ�Ĵ���
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
VOS_UINT32 TAF_APS_RcvPppModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_MODIFY_IND_STRU            *pstPppModifyInd = VOS_NULL_PTR;

    pstPppModifyInd = (PPP_APS_MODIFY_IND_STRU *)pstMsg;

    if (TAF_APS_INVALID_PDPID != TAF_APS_GetPdpIdByPndId(pstPppModifyInd->ucPdnId))
    {
        return VOS_FALSE;
    }

    /* ���򲻽�״̬������ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmPdnInfoChgInd_PreProc
 ��������  : aps�յ�ehsm��pdn��Ϣ�仯��Ϣ��Ԥ����
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
VOS_UINT32 TAF_APS_RcvEhsmPdnInfoChgInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_INFO_CHANGE_IND_STRU  *pstEhsmPdnChgInd = VOS_NULL_PTR;

    pstEhsmPdnChgInd = (EHSM_APS_PDN_INFO_CHANGE_IND_STRU *)pstMsg;

    if (TAF_APS_INVALID_PDPID != TAF_APS_GetPdpIdByCid(pstEhsmPdnChgInd->ucCid))
    {
        return VOS_FALSE;
    }

    /* ���򲻽�״̬������ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppReconnInd_PreProc
 ��������  : �յ�ID_PPP_APS_RECONN_IND��Ϣ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��9��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppReconnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_RECONN_IND_STRU            *pstPppReconnInd = VOS_NULL_PTR;

    pstPppReconnInd = (PPP_APS_RECONN_IND_STRU *)pstMsg;

    if (TAF_APS_INVALID_PDPID != TAF_APS_GetPdpIdByPndId(pstPppReconnInd->ucPdnId))
    {
        return VOS_FALSE;
    }

    /* ���򲻽�״̬������ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvCdsServiceInd_PreProc
 ��������  : �յ�ID_CDS_APS_SERVICE_IND��Ϣ�Ĵ���
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

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvCdsServiceInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CDS_APS_CDATA_SERVICE_IND_STRU     *pstCdsServiceInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstCdsServiceInd = (CDS_APS_CDATA_SERVICE_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        pstPdpEntity     = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        /* ��������ҵ���Ӧ��ʵ�壬��¼��ǰ�Ĵ������� */
        if (pstPdpEntity->ucNsapi == pstCdsServiceInd->ucRabId)
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SetCqosPriReq_PreProc
 ��������  : ����ID_MSG_TAF_PS_SET_CQOS_PRI_REQ��Ϣ
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
VOS_UINT32 TAF_APS_SetCqosPriReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    TAF_PS_SET_1X_CQOS_PRI_REQ_STRU    *pstSetCqosPriReq;

    pstPsMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetCqosPriReq                   = (TAF_PS_SET_1X_CQOS_PRI_REQ_STRU*)(pstPsMsg->aucContent);

    /* ���û����ü�¼��NV���� */

    /* NVδ���壬To Do */

    /* �������ý�� */

    /* ���ش����� */
    TAF_APS_SndSetCqosPriCnf(&(pstSetCqosPriReq->stCtrl),
                              TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsCallEnterDormantInd_PreProc
 ��������  : �յ�ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND��Ϣ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��28��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallEnterDormantInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_CALL_ENTER_DORMANT_IND_STRU *pstDormantInd;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstDormantInd = (TAF_PS_CALL_ENTER_DORMANT_IND_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstDormantInd->ucPdpId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvPsCallEnterDormantInd_PreProc:Wrong PdpId", pstDormantInd->ucPdpId);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiHatExpired_PreProc
 ��������  : APS PreProc when HAT Expired
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��24��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiHatExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ProcEpdszidHatExpired();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiHtExpired_PreProc
 ��������  : APS PreProc when HT Expired
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��24��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiHtExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ProcEpdszidHtExpired();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvMmaEpdszidInfo_PreProc
 ��������  : APS Rcv EPDSZID Info from MMA��Update Current EPDSZID��
             Start Reconnect If current EPDSZID is not in the List
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��24��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvMmaEpdszidInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_APS_EPDSZID_INFO_IND_STRU      *pEpdszidInfoInd = VOS_NULL_PTR;
    TAF_APS_CDATA_EPDSZID_STRU          stCdataEpdszid;
    VOS_UINT8                           ucPdpId;

    pEpdszidInfoInd = (MMA_APS_EPDSZID_INFO_IND_STRU *)pstMsg;

    PS_MEM_SET(&stCdataEpdszid, 0, sizeof(TAF_APS_CDATA_EPDSZID_STRU));
    stCdataEpdszid.usSid  = pEpdszidInfoInd->usSid;
    stCdataEpdszid.usNid  = pEpdszidInfoInd->usNid;
    stCdataEpdszid.ucPzid = pEpdszidInfoInd->ucPzid;

    /* ��ά�ɲ� */
    TAF_APS_TraceEpdszidInfo();

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        /* ��ǰ���״̬��ʵ�崦��Inactive״̬������Ҫ����EPDSZID�ı���������ؽ� */
        if (TAF_APS_STA_INACTIVE == TAF_APS_GetPdpIdMainFsmState(ucPdpId))
        {
            continue;
        }

        /* �������� */
        /* �ǲ��Ǽ�⵽һ����Ч��PDPID���ɷ��ͺ��������Ǹ���ҵ��� */
        TAF_APS_ProcMmaEpdszidInfo(pEpdszidInfoInd->usSid,
                                   pEpdszidInfoInd->usNid,
                                   pEpdszidInfoInd->ucPzid,
                                   ucPdpId);
        return VOS_TRUE;
    }

    /* If Don't Snd Internal Msg Only Update Epdszid */
    TAF_APS_SetCurrEpdszidInfo(&stCdataEpdszid);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXregRegBeginInd_PreProc
 ��������  : XREG send Reg Begin Ind Msg to APS,The msg contains sid/nid/pzid info
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��24��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvXregRegBeginInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XREG_APS_REG_BEGIN_IND_STRU        *pRegBeginInd = VOS_NULL_PTR;

    pRegBeginInd = (XREG_APS_REG_BEGIN_IND_STRU *)pstMsg;

    TAF_APS_ProcXregEpdszidRegBeginInd(pRegBeginInd->usSid,
                                       pRegBeginInd->usNid,
                                       pRegBeginInd->ucPzid);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsInterEpdszidReOrig_PreProc
 ��������  : PreProc Epdszis Re-Orig Req
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��7��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterEpdszidReOrig_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*TO Do: ���������Ӷ�ģ�ںϺ�Ĵ��� */

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsHaiChangeInd_PreProc
 ��������  : �յ�ID_MSG_TAF_PS_HAI_CHANGE_IND��Ϣ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��4��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsHaiChangeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_HAI_CHANGE_IND_STRU         *pstHaiChangeInd;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstHaiChangeInd = (TAF_PS_HAI_CHANGE_IND_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstHaiChangeInd->ucPdpId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvPsHaiChangeInd_PreProc:Wrong PdpId", pstHaiChangeInd->ucPdpId);
        return VOS_TRUE;
    }

    TAF_APS_ProcEpdszidHaiChangeInd();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvXccUpdateDataCallInfoInd_PreProc
 ��������  : The Process for receiving ID_XCC_APS_ANSWER_DATA_CALL_CNF
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
VOS_UINT32 TAF_APS_RcvXccUpdateDataCallInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU     *pstDataCallInfo = VOS_NULL_PTR;
    VOS_UINT8                                   ucPdpId;

    pstDataCallInfo = (XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU *)pstMsg;

    /* If can not find corresponding PDP ID, discard this message */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstDataCallInfo->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccUpdateDataCallInfoInd_PreProc:Wrong CallId", pstDataCallInfo->ucCallId);
        return VOS_TRUE;
    }

    /* Enter FSM to process */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmOrigCnf_PreProc
 ��������  : �յ�ID_HSM_APS_ORIG_CNF��Ϣ�Ĵ���
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
VOS_UINT32 TAF_APS_RcvHsmOrigCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_ORIG_CNF_STRU              *pstOrigCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstOrigCnf = (HSM_APS_ORIG_CNF_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstOrigCnf->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmConnectInd_PreProc
 ��������  : �յ�ID_HSM_APS_CONNECT_IND��Ϣ�Ĵ���
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
VOS_UINT32 TAF_APS_RcvHsmConnectInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;
    TAF_APS_STA_ENUM_UINT32             enStatus;
    VOS_UINT8                           ucPdpId;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* ��ǰֻ֧��dormant״̬�£����緢���Ѱ���������Ч��PDP ID��ֱ������ */
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        /* ���缤��ֻ����DORMANT��TAF_APS_STA_CDATA_ESTING״̬�µ����� */
        enStatus = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
        if ((TAF_APS_STA_DORMANT == enStatus)
          ||(TAF_APS_STA_CDATA_ESTING == enStatus))
        {
            pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

            TAF_APS_SndHsmConnectRsp(pstPdpEntity->stCdataInfo.ucCallId);

            /* ��״̬������ */
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmDiscCnf_PreProc
 ��������  : �յ�ID_HSM_APS_DISC_CNF��Ϣ�Ĵ���
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
VOS_UINT32 TAF_APS_RcvHsmDiscCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_DISC_CNF_STRU              *pstDiscCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstDiscCnf = (HSM_APS_DISC_CNF_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstDiscCnf->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmDiscInd_PreProc
 ��������  : �յ�ID_HSM_APS_DISC_IND��Ϣ�Ĵ���
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
VOS_UINT32 TAF_APS_RcvHsmDiscInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_DISC_IND_STRU              *pstDiscInd     = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstDiscInd = (HSM_APS_DISC_IND_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstDiscInd->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmLocChangedInd_PreProc
 ��������  : �յ�ID_HSM_APS_LOC_CHANGED_IND��Ϣ�Ĵ���
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
VOS_UINT32 TAF_APS_RcvHsmLocChangedInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_LOC_CHANGED_IND_STRU       *pstLocChangedInd = VOS_NULL_PTR;
    TAF_APS_CDATA_EPDSZID_STRU          stCdataEpdszid;

    pstLocChangedInd = (HSM_APS_LOC_CHANGED_IND_STRU *)pstMsg;

    PS_MEM_SET(&stCdataEpdszid, 0, sizeof(TAF_APS_CDATA_EPDSZID_STRU));
    stCdataEpdszid.usSid  = pstLocChangedInd->usSid;
    stCdataEpdszid.usNid  = pstLocChangedInd->usNid;
    stCdataEpdszid.ucPzid = pstLocChangedInd->ucPktZoneId;


    /* ����hrpd���µ�Sid/Nid��Ϣ */
    TAF_APS_SetHrpdEpdszidInfo(pstLocChangedInd->usSid,
                               pstLocChangedInd->usNid,
                               pstLocChangedInd->ucPktZoneId);

    /* ��ά�ɲ� */
    TAF_APS_TraceEpdszidInfo();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsm1XToHrpdHandOff_PreProc
 ��������  : �յ�ID_HSM_APS_1X_TO_HRPD_HANDOFF_CNF��Ϣ�Ĵ���
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
VOS_UINT32 TAF_APS_RcvHsm1XToHrpdHandOff_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                     ucPdpId;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmHrpdAvailableIndPreProc
 ��������  : �յ�ID_HSM_APS_HRPD_AVAILABLE_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��07��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmHrpdAvailableIndPreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_SetIsHrpdDisabledFlag(VOS_FALSE);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsSetPktCdataInactivityTimeLenReq_PreProc
 ��������  : ��ϢID_MSG_TAF_PS_SET_1X_MAX_NO_DATA_TIME_LEN_REQԤ������
 �������  : ulEventType --- �¼���
             pstMsg      --- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE    --- ��Ϣ�������
             VOS_FALSE   --- ��Ϣδ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��21��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��1��25��
    ��    ��   : y00322978
    �޸�����   : DTS2016012503506 at+cta����1x��do�Ľ���dormant̬��ʱ��
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsSetPktCdataInactivityTimeLenReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_SET_CTA_INFO_REQ_STRU       *pstSetPktCdataInactivityTimeLenReq = VOS_NULL_PTR;

    pstSetPktCdataInactivityTimeLenReq = (TAF_PS_SET_CTA_INFO_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);

    TAF_APS_SetPktCdataInactivityTimerLen(pstSetPktCdataInactivityTimeLenReq->ucPktCdataInactivityTmrLen);

    TAF_APS_SndSetPktCdataInactivityTimerLenCnf(&(pstSetPktCdataInactivityTimeLenReq->stCtrl), TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsGetPktCdataInactivityTimerLenReq_PreProc
 ��������  : ��ϢID_MSG_TAF_PS_SET_1X_MAX_NO_DATA_TIME_LEN_REQԤ������
 �������  : ulEventType --- �¼���
             pstMsg      --- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE    --- ��Ϣ�������
             VOS_FALSE   --- ��Ϣδ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��21��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsGetPktCdataInactivityTimerLenReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_GET_CTA_INFO_REQ_STRU       *pstGetPktCdataInactivityTmrlenReq = VOS_NULL_PTR;
    VOS_UINT8                                               ucTimeLen;

    pstGetPktCdataInactivityTmrlenReq  = (TAF_PS_GET_CTA_INFO_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);

    ucTimeLen = TAF_APS_GetPktCdataInactivityTimerLen();

    if (0 == ucTimeLen)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvPsGetPktCdataInactivityTimerLenReq_PreProc:Time Len = 0!");
    }

    TAF_APS_SndGetPktCdataInactivityTimerLenCnf(&(pstGetPktCdataInactivityTmrlenReq->stCtrl), ucTimeLen, TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPowerOnInd_Preproc
 ��������  : �ӿ��ж�ȡ����ҵ��ʱ����������շ�ʱ������
 �������  : ulEventType --- �¼���
             pstMsg      --- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE    --- ��Ϣ�������
             VOS_FALSE   --- ��Ϣδ����

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��21��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPowerOnInd_Preproc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��RLPע����������״̬�Ļص�����*/
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        CTTF_HRPD_RPA_RegDormancyMonitor(TAF_APS_ProcEvdoRlpDataStatusCb);

        CTTF_1X_RLP_RegUserDataUpdateCB(WUEPS_PID_TAF,TAF_APS_ProcRlpDataStatusCb);
    }

    if (VOS_TRUE != TAF_SDC_Is1xOnlyMode())
    {
        TAF_APS_SetClDelaySearch(VOS_TRUE);
    }
    else
    {
        TAF_APS_SetClDelaySearch(VOS_FALSE);
    }

    if (VOS_TRUE == TAF_APS_GetPppAuthInfoGetFromCardFlag())
    {
        TAF_APS_SetRead3GpdFileDoneFlag(VOS_FALSE);
        TAF_APS_Read3GdpFile();
    }
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetDialModeReq_PreProc
 ��������  :
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��02��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsSetDialModeReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_CDATA_DIAL_MODE_REQ_STRU    *pstDialModeReq = VOS_NULL_PTR;
    TAF_PS_MSG_STRU                    *pstPsMsg       = VOS_NULL_PTR;

    /* ��ʼ�� */
    pstDialModeReq    = (TAF_PS_CDATA_DIAL_MODE_REQ_STRU *)pstMsg;

    /* ȥ��Ϣͷ, �ظ�AT */
    pstPsMsg          = (TAF_PS_MSG_STRU *)pstMsg;
    pstDialModeReq    = (TAF_PS_CDATA_DIAL_MODE_REQ_STRU *)pstPsMsg->aucContent;

    TAF_APS_SetFsmCtxCdataDialMode(pstDialModeReq->enDialMode);

    TAF_APS_SndPppDialModeNotify(pstDialModeReq->stCtrl.usClientId);

    TAF_APS_SndSetDialModeCnf(&(pstDialModeReq->stCtrl), TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_RcvGetCgmtuValue_PreProc
 ��������  : TAF APS Pre Proc CDMA Mtu Value Qry Req
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��29��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvGetCgmtuValue_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_GET_CGMTU_VALUE_REQ_STRU    *pstCgmtuValueReq = VOS_NULL_PTR;
    VOS_UINT32                          ulMtuValue;

    pstCgmtuValueReq = (TAF_PS_GET_CGMTU_VALUE_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);

    ulMtuValue       = TAF_APS_GET_CDATA_MTU();

    TAF_APS_SndGetCgmtuValueCnf(&(pstCgmtuValueReq->stCtrl), ulMtuValue);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvMma1XServiceStatusInd_PreProc
 ��������  : �յ�ID_MMA_TAF_1X_SERVICE_STATUS_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��08��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvMma1XServiceStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_TAF_1X_SERVICE_STATUS_IND_STRU *pstMmaServiceStatusInd = VOS_NULL_PTR;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enOldRatType;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enNewRatType;
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��Ϣ���� */
    pstMmaServiceStatusInd = (MMA_TAF_1X_SERVICE_STATUS_IND_STRU*)pstMsg;

    /* ����1X��PS�����״̬��Ϣ */
    TAF_APS_Set1XPsServiceStatus(pstMmaServiceStatusInd->ulExist1XService);

    enOldRatType = TAF_APS_GetCurrPdpEntityRatType();

    /* �ж�syscfg���ã������֧��CDMA��ֱ���˳� */
    if (VOS_TRUE != TAF_SDC_IsConfigCLMode())
    {
        return VOS_TRUE;
    }

    /* ���ֻ֧��1X����ֱ��ȡ1X�ķ���״̬ */
    if (VOS_TRUE == TAF_SDC_Is1xOnlyMode())
    {
        /* 1X��PS��������ʱ��ȡ1X�ķ��� */
        enNewRatType = (pstMmaServiceStatusInd->ulExist1XService ? TAF_APS_RAT_TYPE_1X:TAF_APS_RAT_TYPE_NULL);

    }
    else
    {
        if ((VOS_FALSE == TAF_APS_GetClDelaySearch())
         && (TAF_APS_RAT_TYPE_NULL == enOldRatType)
         && (VOS_TRUE  == pstMmaServiceStatusInd->ulExist1XService))
         {
            /* ֮ǰ���κ�PS�����1X��PS��������ʱ��ȡ1X�ķ��� */
            enNewRatType = TAF_APS_RAT_TYPE_1X;
         }
         else if((TAF_APS_RAT_TYPE_1X == enOldRatType)
              && (VOS_FALSE == pstMmaServiceStatusInd->ulExist1XService))
         {
            /* ֮ǰΪ1X��PS�����1X��PS����񲻿���ʱ��ȡNULL */
            enNewRatType = TAF_APS_RAT_TYPE_NULL;
         }
         else
         {
            /* ���������ȡԭ��¼:NULL false,1x true */
            enNewRatType = TAF_APS_GetCurrPdpEntityRatType();
         }
    }

    TAF_APS_LogOldNewPdpRatType(enNewRatType, enOldRatType);

    /* ����״̬��ʵ����뼼�� */
    TAF_APS_SetCurrPdpEntityRatType(enNewRatType);


    if ((TAF_APS_RAT_TYPE_NULL == enNewRatType)
     && (enOldRatType == enNewRatType))
    {
        return VOS_TRUE;
    }

    /* TO DO:Ԥ��������Ehsm����Loc Detach Ind��Ϣ */

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* �����ǰPDPʵ�岻ΪINACTIVE״̬�������ڲ���Ϣ��״̬������ */
        if (VOS_TRUE == TAF_APS_IsPdpIdValid(ucPdpId))
        {
            (VOS_VOID)TAF_APS_SndInterServiceStatusChangeInd(ucPdpId,
                                                   TAF_APS_GetCurrPdpEntityRatType(),
                                                   enOldRatType,
                                                   TAF_APS_GetCurrPdpEntitySimRegStatus(),
                                                   VOS_FALSE,
                                                   TAF_APS_INTER_SERVICE_RESULT_1X);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvMmaCLServiceStatusInd_PreProc
 ��������  : �յ�ID_MMA_TAF_SERVICE_STATUS_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��08��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvMmaCLServiceStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_APS_CL_SERVICE_STATUS_IND_STRU *pstMmaServiceStatusInd = VOS_NULL_PTR;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enOldRatType;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enNewRatType;
    VOS_UINT32                          ulExist1XService;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrDataServiceMode;
    VOS_UINT8                           ucPdpId;


    /* ��ȡ��Ϣ���� */
    pstMmaServiceStatusInd  = (MMA_APS_CL_SERVICE_STATUS_IND_STRU*)pstMsg;
    ulExist1XService        = TAF_APS_Get1XPsServiceStatus();
    enOldRatType            = TAF_APS_GetCurrPdpEntityRatType();
    enNewRatType            = enOldRatType;

    /* �ж�syscfg���ã������֧��CDMA��ֱ���˳� */
    if (VOS_TRUE != TAF_SDC_IsConfigCLMode())
    {
        return VOS_TRUE;
    }


    /* DO/LTE���з����޷���ʱ�Ĵ��� */
    if ((MMA_TAF_CL_STATUS_DO_LTE_NO_SERVICE == pstMmaServiceStatusInd->enClStatus)
     || (MMA_TAF_CL_STATUS_DO_NO_SERVICE     == pstMmaServiceStatusInd->enClStatus)
     || (MMA_TAF_CL_STATUS_LTE_NO_SERVICE    == pstMmaServiceStatusInd->enClStatus))
    {
        /* ��ǰ1X�з����յ�DO��LTE�޷��񣬲����½��뼼��ģʽ */
        if (VOS_TRUE == ulExist1XService)
        {
            if (TAF_APS_CDMA_TC_SUSPENDED != TAF_APS_GET_CDATA_SUSPEND_STATUS())
            {
                enNewRatType = TAF_APS_RAT_TYPE_1X;
            }
            else
            {
                enNewRatType = TAF_APS_RAT_TYPE_NULL;
            }
        }
        else
        {
            enNewRatType = TAF_APS_RAT_TYPE_NULL;
        }
    }
    else
    {
        enNewRatType = TAF_APS_ConvertMmaClServiceToApsRatType(pstMmaServiceStatusInd->enClStatus);
    }

    TAF_APS_LogOldNewPdpRatType(enNewRatType, enOldRatType);

    /* ����״̬��ʵ����뼼�� */
    TAF_APS_SetCurrPdpEntityRatType(enNewRatType);

    if ((TAF_APS_RAT_TYPE_HRPD  == enNewRatType)
     || (TAF_APS_RAT_TYPE_EHRPD == enNewRatType)
     || (TAF_APS_RAT_TYPE_LTE   == enNewRatType))
    {
        TAF_APS_SetClDelaySearch(VOS_TRUE);
    }
    else
    {
        TAF_APS_SetClDelaySearch(VOS_FALSE);
    }

    /* ֪ͨCDS��ǰ���뼼���ı� */
    enCurrDataServiceMode = TAF_APS_GetCurrPdpEntityDataServiceMode();
    if (VOS_TRUE == TAF_APS_IsNeedNotifyCdsModeChange(enNewRatType, enCurrDataServiceMode))
    {
        TAF_APS_SndCdsModeChangeInd(enNewRatType);
    }

    /* ģʽû�иı����ٴν���״̬�����������ظ��������������Ϣ */
    if ((enOldRatType          == enNewRatType)
     && (TAF_APS_RAT_TYPE_NULL == enNewRatType))
    {
        return VOS_TRUE;
    }

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* �����ǰPDPʵ�岻ΪINACTIVE״̬�������ڲ���Ϣ��״̬������ */
        if (VOS_TRUE == TAF_APS_IsPdpIdValid(ucPdpId))
        {
            (VOS_VOID)TAF_APS_SndInterServiceStatusChangeInd(ucPdpId,
                                                   TAF_APS_GetCurrPdpEntityRatType(),
                                                   enOldRatType,
                                                   TAF_APS_GetCurrPdpEntitySimRegStatus(),
                                                   pstMmaServiceStatusInd->ucIsNewSession,
                                                   TAF_APS_INTER_SERVICE_RESULT_CL);
        }
    }

    return VOS_TRUE;
}


#if 0
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvMmaHrpdDataCallSysAcqInd_PreProc
 ��������  : �յ�ID_MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvMmaHrpdDataCallSysAcqInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND_STRU                *pstHrpdSysAcqInd = VOS_NULL_PTR;

    pstHrpdSysAcqInd = (MMA_APS_HRPD_DATA_CALL_SYS_ACQ_IND_STRU *)pstMsg;

    if (MMA_TAF_HRPD_ACQUIRED_RESULT_SUCC == pstHrpdSysAcqInd->enHrpdSysAcqRst)
    {
        /* Ŀǰ��Ϣ��Я����rattype������ */
        if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_ConvertMmaRatType(pstHrpdSysAcqInd->enRatType))
        {
            TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_HRPD);
        }
        else
        {
            TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_EHRPD);
        }

    }

    return VOS_FALSE;
}

#endif

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvMmaSysCfgInfoInd_PreProc
 ��������  : �յ�ID_MMA_APS_SYS_CFG_INFO_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��29��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvMmaSysCfgInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_TAF_SYS_CFG_INFO_IND_STRU      *pstSysCfgInfoInd = VOS_NULL_PTR;
    VOS_UINT8                           i;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType;

    pstSysCfgInfoInd = (MMA_TAF_SYS_CFG_INFO_IND_STRU *)pstMsg;


    /* ϵͳģʽ�л�GUL<->CL�л���APS�������������Ϣ���˳�״̬������֪ͨ�ײ�ģ�飬�����ͬ��POWER_OFF
       1.GUL->CL ����ȥ�����APS֪ͨSM��ESM��ADS��CDS��ģ�飻
       2.CL->GUL ����ȥ�����APS֪ͨEHSM��ESM��ADS��CDS��PPP��ģ�飻
       ע�����ϵ�CL�ǹ�������壬��������ģʽ��1X only��DO only��hybrid��1X+LTE��hybrid+LTE(SVLTE)��
    */

    if (VOS_TRUE == TAF_APS_IsSyscfgCdmaModeChange(&pstSysCfgInfoInd->stOldRatOrder,
                                                   &pstSysCfgInfoInd->stNewRatOrder))
    {
        TAF_APS_LocalReleaseAll();
    }

    /* �ǵ�1Xʱ�����ͱ��ΪVOS_FALSE */
    for (i = 0; i < pstSysCfgInfoInd->stNewRatOrder.ucRatOrderNum; i++)
    {
        enRatType = TAF_APS_ConvertMmaRatTypeToApsRatType(pstSysCfgInfoInd->stNewRatOrder.aenRatOrder[i]);

        if ((TAF_APS_RAT_TYPE_HRPD == enRatType)
         || (TAF_APS_RAT_TYPE_LTE  == enRatType))
        {
            TAF_APS_SetClDelaySearch(VOS_TRUE);

            return VOS_TRUE;
        }
    }

    /* ��1Xʱ�����ͱ��ΪVOS_FALSE */
    enRatType = TAF_APS_ConvertMmaRatTypeToApsRatType(pstSysCfgInfoInd->stNewRatOrder.aenRatOrder[0]);
    if ((1                   == pstSysCfgInfoInd->stNewRatOrder.ucRatOrderNum)
     && (TAF_APS_RAT_TYPE_1X == enRatType))
    {
        TAF_APS_SetClDelaySearch(VOS_FALSE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmPdnActiveInd_PreProc
 ��������  : �յ�ID_EHSM_APS_PDN_ACTIVATE_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnActInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ACTIVATE_IND_STRU     *pstEhsmPdnInd;
    VOS_UINT8                           ucPdpId;
    TAF_CTRL_STRU                       stCtrl;

    pstEhsmPdnInd = (EHSM_APS_PDN_ACTIVATE_IND_STRU *)pstMsg;
    /* MODULE IDĬ������ΪAT */
    stCtrl.ulModuleId   = WUEPS_PID_AT;
    stCtrl.usClientId   = TAF_APS_INVALID_CLIENTID;
    stCtrl.ucOpId       = TAF_APS_INVALID_OPID;

    /* Cid��ֵ��Ч����ֱ�ӷ��� */
    if ( TAF_INVALID_CID == pstEhsmPdnInd->ucCid )
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvEhsmPdnActInd_PreProc:invalid Cid", pstEhsmPdnInd->ucCid);
        return VOS_TRUE;
    }

#if 0
    /* ��������£�����CID������Pdp Id */
    ucPdpId = TAF_APS_GetPdpIdByCid(pstEhsmPdnInd->ucCid);
    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        return VOS_FALSE;
    }
    else
    {
        /* �Զ�Ӧ��ģʽ��, ��Ҫ�����µ�APSʵ�����洢������Ϣ */
        TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEhsmPdnActInd_PreProc, Get PDP ID fail.");
    }
#endif

    /* cidΪ0ʱ����ʾ��Ĭ�ϳ��أ������һ���µ�PDP ID
       client id��op id��ʱ��Ϊ����Чֵ��������������ʱ���ٽ���ˢ�� */
    if (TAF_APS_DEFAULT_CID == pstEhsmPdnInd->ucCid)
    {
        /* ����(PdP Id) */
        if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&stCtrl,
                                                           pstEhsmPdnInd->ucCid,
                                                           &ucPdpId))
        {
            /* ���䲻��ʵ�壬��ӡ�쳣����ʱ��Ӧ�÷��䲻��ʵ�� */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEhsmPdnActInd_PreProc, alloc pdp id fail");
            return VOS_TRUE;
        }
    }
    else
    {
        /* �쳣��Ϣ, ���� */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEhsmPdnActInd_PreProc, Abnormal Ehsm CID.");
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmPdnDeactiveInd_PreProc
 ��������  : �յ�ID_EHSM_APS_PDN_DEACTIVATE_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnDeactInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_DEACTIVATE_IND_STRU   *pstPdnDeactInd;

    pstPdnDeactInd = (EHSM_APS_PDN_DEACTIVATE_IND_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByPndId(pstPdnDeactInd->ucPdnId))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmLteHandoverToEhrpdInd_PreProc
 ��������  : �յ�ID_MMA_TAF_SERVICE_STATUS_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��11��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmLteHandoverToEhrpdInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU       *pstPdnIratHrpdInd;

    pstPdnIratHrpdInd = (EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByNsapi(pstPdnIratHrpdInd->ucRabId))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    /* ��¼��ǰ��PS�������ڵ�ģʽ */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_EHRPD);

    /* �����״̬������ */
    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmPdnActCnf_PreProc
 ��������  : �յ�ID_EHSM_APS_PDN_ACTIVATE_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��19��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnActCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ACTIVATE_CNF_STRU     *pstPdnActCnf;

    pstPdnActCnf = (EHSM_APS_PDN_ACTIVATE_CNF_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPdnActCnf->ucCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmPdnAttachCnf_PreProc
 ��������  : ID_EHSM_APS_PDN_ATTACH_CNF��Ϣ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��30��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnAttachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ATTACH_CNF_STRU       *pstPdnAttachCnf;

    pstPdnAttachCnf = (EHSM_APS_PDN_ATTACH_CNF_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPdnAttachCnf->ucCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmPdnDeactCnf_PreProc
 ��������  : �յ�ID_EHSM_APS_PDN_DEACTIVATE_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnDeactCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_DEACTIVATE_CNF_STRU   *pstPdnDeactCnf;

    pstPdnDeactCnf = (EHSM_APS_PDN_DEACTIVATE_CNF_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPdnDeactCnf->ucCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmReconnCnf_PreProc
 ��������  : �յ�ID_EHSM_APS_RECONN_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmReconnCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_RECONN_CNF_STRU           *pstReconnCnf;
    VOS_UINT8                           ucPdpId;

    pstReconnCnf = (EHSM_APS_RECONN_CNF_STRU *)pstMsg;
    ucPdpId      = TAF_APS_GetPdpIdByCid(pstReconnCnf->ucCid);

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }


    /* ��CDS����ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND��Ϣ */
    TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvDhcpDnsGetCnf_PreProc
 ��������  : �յ�DHCP��ID_DHCP_APS_GET_DNS_IPV4_CNF��Ϣ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��24��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvDhcpDnsIpv4Cnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    DHCP_APS_DNS_IPV4_CNF_STRU         *pstDhcpDnsIpv4Cnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstDhcpDnsIpv4Cnf = (DHCP_APS_DNS_IPV4_CNF_STRU *)pstMsg;

    /* ��ȡNSAPI��Ӧ��APSʵ�� */
    ucPdpId           = TAF_APS_GetPdpIdByNsapi(pstDhcpDnsIpv4Cnf->ucRabId);

    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);
        pstPdpEntity      = TAF_APS_GetPdpEntInfoAddr(ucPdpId);


        if (VOS_OK             == pstDhcpDnsIpv4Cnf->ulResult)
        {
            /* ����PDPʵ���DNS */
            TAF_APS_UpdateCdataIpv4Dns(pstPdpEntity, pstDhcpDnsIpv4Cnf);
        }
        else
        {
            /* Э��ʧ�ܴ��� */
            TAF_APS_ProcCdataDhcpNegotiateFail(ucPdpId,
                                               TAF_APS_INTER_END_CALL_REASON_DHCP_ACT_IPV4_FAIL);

            return VOS_TRUE;
        }

        TAF_APS_IpfConfigUlFilter(ucPdpId);

        if (APS_ADDR_STATIC_IPV4 == pstPdpEntity->PdpAddr.ucPdpTypeNum)
        {
            /* Э�̽��� */
            pstPdpEntity->ucNeedGetDnsFlg = VOS_FALSE;

            if (TAF_APS_DEFAULT_CID != ucCid)
            {
                /* ���û��ϱ�ACTIVATE_CNF�¼� */
                TAF_APS_SndPdpActivateCnf(ucPdpId, ucCid);
            }

            return VOS_TRUE;
        }
        else
        {
            /* �����Ipv4Ipv6, �����ñ�IPV4�ı�־λ */
            pstPdpEntity->ucRcvDhcpDnsFlgIpv4 = VOS_TRUE;
        }

         /* ��ǰΪIpv4v6, �� RaInfo*/
        TAF_APS_RcvSequenceProcessDhcpNdclient(ucPdpId, ucCid);


    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvDhcpDnsIpv4Cnf_PreProc: Can't find PDP ID form RAB ID!");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvDhcpDnsIpv6Cnf_PreProc
 ��������  : �յ�DHCP��ID_DHCP_APS_GET_DNS_IPV6_CNF��Ϣ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��24��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvDhcpDnsIpv6Cnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    DHCP_APS_DNS_IPV6_CNF_STRU         *pstDhcpDnsIpv6Cnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    MN_APS_PDP_IPV6_DNS_STRU           *pstPdpIpv6Dns;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstDhcpDnsIpv6Cnf = (DHCP_APS_DNS_IPV6_CNF_STRU *)pstMsg;

    /* ��ȡNSAPI��Ӧ��APSʵ�� */
    ucPdpId           = TAF_APS_GetPdpIdByNsapi(pstDhcpDnsIpv6Cnf->ucRabId);

    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);
        pstPdpEntity      = TAF_APS_GetPdpEntInfoAddr(ucPdpId);


        if (VOS_OK             == pstDhcpDnsIpv6Cnf->ulResult)
        {
            /* ����PDPʵ���DNS */
            pstPdpIpv6Dns = (MN_APS_PDP_IPV6_DNS_STRU *)&pstDhcpDnsIpv6Cnf->stIpv6Dns;

            TAF_APS_UpdateCdataIpv6Dns(pstPdpEntity, pstPdpIpv6Dns);
        }
        else
        {
            pstPdpIpv6Dns = (MN_APS_PDP_IPV6_DNS_STRU *)&pstDhcpDnsIpv6Cnf->stIpv6Dns;
            PS_MEM_SET(pstPdpIpv6Dns, 0, sizeof(MN_APS_PDP_IPV6_DNS_STRU));

            TAF_APS_UpdateCdataIpv6Dns(pstPdpEntity, pstPdpIpv6Dns);

            /* Э��ʧ�ܴ��� */
#if 0
            TAF_APS_ProcCdataDhcpNegotiateFail(ucPdpId,
                                               TAF_APS_INTER_END_CALL_REASON_DHCP_ACT_IPV6_FAIL);

            return VOS_TRUE;
#endif
        }

        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* Ipv4Ipv6, �����ñ�IPV6�ı�־λ
            ��ֻ��IPV6��Э��   */
        pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_TRUE;

        /* ��ǰΪIpv4 v6, ��Ҫ�жϱ�־λ���������ĸ�������Ϣ�ϱ� ipv4Cnf ipv6Cnf ndclientInd */
        TAF_APS_RcvSequenceProcessDhcpNdclient(ucPdpId, ucCid);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvDhcpDnsIpv6Cnf_PreProc: Can't find PDP ID form RAB ID!");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterPsServiceModeModifyInd_PreProc
 ��������  : �յ�ID_MSG_TAF_PS_INTER_PS_SERVICE_MODE_MODIFY_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��4��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterPsServiceModeModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU   *pstInterMsg = VOS_NULL_PTR;
    TAF_APS_RAT_TYPE_ENUM_UINT32                         enPsRatType;
    TAF_APS_RAT_TYPE_ENUM_UINT32                         enPsDataSerMode;
    VOS_UINT8                                            ucPdpId;

    pstInterMsg     = (TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU *)pstMsg;

    enPsRatType     = TAF_APS_GetCurrPdpEntityRatType();
    enPsDataSerMode = TAF_APS_GetCurrPdpEntityDataServiceMode();

    switch (pstInterMsg->enPsOptionType)
    {
        case TAF_APS_INTER_PS_OPTION_DISCONNECTED:
            for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
            {
                if (VOS_TRUE == TAF_APS_IsPdpIdValid(ucPdpId))
                {
                    /* ȥ�������������ڳ��أ�����PSģʽ��rattypeһ�� */
                    if ((enPsRatType != enPsDataSerMode)
                     && (  (TAF_APS_RAT_TYPE_HRPD == enPsDataSerMode)
                         ||(TAF_APS_RAT_TYPE_1X   == enPsDataSerMode)))
                    {
                        break;
                    }
                    else
                    {
                        return VOS_TRUE;
                    }
                }
            }

            /* ��ǰ��PSҵ�� */
            enPsRatType = TAF_APS_RAT_TYPE_NULL;
            break;

        case TAF_APS_INTER_PS_OPTION_SWITCH:

            break;

        default:
            return VOS_TRUE;
    }

    /* ���õ�ǰPSҵ�����ڵ�ģʽ */
    TAF_APS_SetCurrPdpEntityDataServiceMode(enPsRatType);

    /* ֪ͨ�ⲿģ�鵱ǰPSҵ�����ڵ�ģʽ */
    TAF_APS_SndExternalModulePsRatTypeNtf(enPsRatType);

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSet1xDormantTimer_PreProc
 ��������  : ��ϢID_MSG_TAF_PS_SET_1X_MAX_NO_DATA_TIME_LEN_REQԤ������
 �������  : ulEventType --- �¼���
             pstMsg      --- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE    --- ��Ϣ�������
             VOS_FALSE   --- ��Ϣδ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��13��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSet1xDormantTimer_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_SET_1X_DORM_TIMER_REQ_STRU  *pstSet1xDormTimerReq = VOS_NULL_PTR;
    VOS_UINT32                          ulSocmDormTimer;
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_PS_SET_1X_DORM_TIMER_CNF_STRU   stSet1xDormTimerCnf;

    enCause              = TAF_PS_CAUSE_SUCCESS;
    pstSet1xDormTimerReq = (TAF_PS_SET_1X_DORM_TIMER_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    ulSocmDormTimer      = TAF_APS_GetSocmDormantTiLen();

    /* Dormant timer feature is enable, and user cfg value shall not less than SOCM setting  */
    if ((ulSocmDormTimer > 0) && ((pstSet1xDormTimerReq->ucDormantTimer * 100) >= ulSocmDormTimer))
    {
        TAF_APS_SetUserCfgDormTiVal(pstSet1xDormTimerReq->ucDormantTimer * 100);
    }
    else
    {
        enCause       = TAF_PS_CAUSE_INVALID_PARAMETER;
    }

    PS_MEM_SET(&stSet1xDormTimerCnf, 0, sizeof(TAF_PS_SET_1X_DORM_TIMER_CNF_STRU));

    /* ��д��Ϣͷ */
    stSet1xDormTimerCnf.stCtrl  = pstSet1xDormTimerReq->stCtrl;
    stSet1xDormTimerCnf.enCause = enCause;

    /* ����ID_EVT_TAF_PS_SET_1X_DORM_TIMER_CNF��Ϣ */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_1X_DORM_TIMER_CNF,
                               &stSet1xDormTimerCnf,
                               sizeof(TAF_PS_SET_1X_DORM_TIMER_CNF_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGet1xDormantTimer_PreProc
 ��������  : ��ϢID_MSG_TAF_PS_SET_1X_MAX_NO_DATA_TIME_LEN_REQԤ������
 �������  : ulEventType --- �¼���
             pstMsg      --- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE    --- ��Ϣ�������
             VOS_FALSE   --- ��Ϣδ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��13��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGet1xDormantTimer_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_GET_1X_DORM_TIMER_REQ_STRU  *pstGet1xDormTimerReq = VOS_NULL_PTR;
    TAF_PS_GET_1X_DORM_TIMER_CNF_STRU   stGet1xDormTimerCnf;

    pstGet1xDormTimerReq = (TAF_PS_GET_1X_DORM_TIMER_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);

    PS_MEM_SET(&stGet1xDormTimerCnf, 0, sizeof(TAF_PS_GET_1X_DORM_TIMER_CNF_STRU));

    /* ��д��Ϣͷ */
    stGet1xDormTimerCnf.stCtrl             = pstGet1xDormTimerReq->stCtrl;
    stGet1xDormTimerCnf.ucSocmDormTiVal    = (VOS_UINT8)(TAF_APS_GetSocmDormantTiLen()/100);
    stGet1xDormTimerCnf.ucUserCfgDormTival = (VOS_UINT8)(TAF_APS_GetUserCfgDormTiVal()/100);

    /* ����ID_EVT_TAF_PS_SET_1X_DORM_TIMER_CNF��Ϣ */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_1X_DORM_TIMER_CNF,
                               &stGet1xDormTimerCnf,
                               sizeof(TAF_PS_GET_1X_DORM_TIMER_CNF_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_UsimGetFileRspPreProc
 ��������  : aps �յ����ļ���ȡcnf��Ϣ�Ĵ���
 �������  : USIMM_READFILE_CNF_STRU* pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��27��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_UsimGetFileRspPreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pUsimTafMsg  = VOS_NULL_PTR;
    USIMM_DEF_FILEID_ENUM_UINT32        enFileID;

    pUsimTafMsg = (USIMM_READFILE_CNF_STRU *)pstMsg;
    if (VOS_OK != USIMM_ChangePathToDefFileID(pUsimTafMsg->stCmdResult.enApptype, pUsimTafMsg->stFilePath.ulPathLen, pUsimTafMsg->stFilePath.acPath, &enFileID))
    {
        return VOS_FALSE;
    }

    /* ����ȴ���� */
    TAF_APS_ClearWaitSimFilesCnfFlg(enFileID);

    if (TAF_APS_READ_USIM_FILE_FLG_NULL == TAF_APS_GetWaitSimFilesCnfFlg())
    {
        TAF_APS_SetRead3GpdFileDoneFlag(VOS_TRUE);
    }


    switch (enFileID)
    {
        case USIMM_CDMA_EFSIPCAP_ID:
        case USIMM_CSIM_EFSIPCAP_ID:
            TAF_APS_Read3GpdSipCapaFileCnf(pUsimTafMsg);
            break;
        case USIMM_CDMA_EFSIPUPP_ID:
        case USIMM_CSIM_EFSIPUPP_ID:
            TAF_APS_Read3GpdSipUppFileCnf(pUsimTafMsg);
            break;
        case USIMM_CDMA_EFSIPSP_ID:
        case USIMM_CSIM_EFSIPSP_ID:
            TAF_APS_Read3GpdSipStatusFileCnf(pUsimTafMsg);
            break;
        case USIMM_CDMA_EFSIPPAPSS_ID:
        case USIMM_CSIM_EFSIPPAPSS_ID:
            TAF_APS_Read3GpdSipPapSsFileCnf(pUsimTafMsg);
            break;
        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_UsimGetFileRspPreProc():WARNING:UNKNOW EFID RECEIVE! ");
    }

    return VOS_TRUE;
}


#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
