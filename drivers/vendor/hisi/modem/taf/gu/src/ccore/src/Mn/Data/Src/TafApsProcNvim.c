/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsProcNvim.c
  �� �� ��   : ����
  ��    ��   : o00132663
  ��������   : 2011��12��15��
  ����޸�   :
  ��������   : ����NVIM��ȡ��غ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��12��15��
    ��    ��   : o00132663
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsCommonDef.h"
#include "NVIM_Interface.h"
#include "TafApsProcNvim.h"
#include "TafApsDsFlowStats.h"
#include "TafLog.h"
#include "TafApsCtx.h"
#include "TafSdcLib.h"
#include "TafApsMntn.h"
#include "TafApsProcIpFilter.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define THIS_FILE_ID PS_FILE_ID_TAF_APS_PROCNVIM_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_APS_ReadDsFlowInfoFromNv
 ��������  : ��NV�ж�ȡ����ͳ�������Ϣ
 �������  : pstApsDsFlowCtx  - APS����ͳ��������ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��30��
    ��    ��   : z60575
    �޸�����   : DTS2012052907939,����дNVʱ��������NV����
  3.��    ��   : 2012��11��09��
    ��    ��   : l00198894
    �޸�����   : Probe·�⹤�߶Խ���Ŀ�޸�AT�˿������ϱ���־λ
  4.��    ��   : 2013��4��7��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
*****************************************************************************/
VOS_VOID  TAF_APS_ReadDsFlowInfoFromNv(
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx
)
{
    TAF_APS_DSFLOW_NV_STRU              stApsDsflowNv;
    TAF_APS_DSFLOW_STATS_CTRL_NV_STRU   stApsDsflowCtrlNv;

    /* ��ʼ�� */
    PS_MEM_SET(&stApsDsflowNv, 0, sizeof(TAF_APS_DSFLOW_NV_STRU));
    PS_MEM_SET(&stApsDsflowCtrlNv, 0, sizeof(TAF_APS_DSFLOW_STATS_CTRL_NV_STRU));

    /* ��NV�ж�ȡ����ͳ��NV�� */
    if (NV_OK != NV_Read (en_NV_Item_DSFLOW_STATS_CTRL,
                          &stApsDsflowCtrlNv, sizeof(TAF_APS_DSFLOW_STATS_CTRL_NV_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_ReadDsFlowCfgFromNv(): NV_Read en_NV_Item_DSFLOW_STATS_CTRL Error");

        /* �����ϱ��ͱ���NV���ƾ���ΪFALSE */
        /* Modified by s00217060 for �����ϱ�AT�������������C��, 2013-4-7, begin */
        pstApsDsFlowCtx->ucDsFlowSave2NvFlg     = VOS_FALSE;
        pstApsDsFlowCtx->ucDsFlowSavePeriod     = TI_TAF_APS_DEFAULT_DSFLOW_WRITE_NV_LEN;
        pstApsDsFlowCtx->ucDsFlowATRptPeriod    = TAF_APS_DSFLOW_AT_REPORT_PERIOD;

        /* ���µ�SDCȫ�ֱ����� */
        TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_DSFLOWRPT, VOS_FALSE);
        return;
    }

    /* ˢ������ͳ�ƿ��������� */
    pstApsDsFlowCtx->ucDsFlowSave2NvFlg     = stApsDsflowCtrlNv.ucDsFlowStatsSave2NvCtrl;
    pstApsDsFlowCtx->ucDsFlowSavePeriod     = stApsDsflowCtrlNv.ucDsFlowSavePeriod;
    pstApsDsFlowCtx->ucDsFlowATRptPeriod    = TAF_APS_DSFLOW_AT_REPORT_PERIOD;

    /* ���µ�SDCȫ�ֱ����� */
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_DSFLOWRPT, (VOS_UINT32)stApsDsflowCtrlNv.ucDsFlowStatsRptCtrl);
	/* Modified by s00217060 for �����ϱ�AT�������������C��, 2013-4-7, end */


    /* ������ʷ��������ʹ�� */
    if ( VOS_TRUE == pstApsDsFlowCtx->ucDsFlowSave2NvFlg )
    {
        if (NV_OK != NV_Read (en_NV_Item_DSFLOW_REPORT,
                              &stApsDsflowNv, sizeof(TAF_APS_DSFLOW_NV_STRU)))
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_ReadDsFlowCfgFromNv(): NV_Read en_NV_Item_DSFLOW_REPORT Error");
            return;
        }


        /* ��ʷ������Ϣ,Ĭ��Ϊ1 */
        pstApsDsFlowCtx->astApsDsFlowStats[0].stCurrentFlowInfo.ulDSLinkTime
                                        = stApsDsflowNv.ulDSLastLinkTime;

        pstApsDsFlowCtx->astApsDsFlowStats[0].stTotalFlowInfo.ulDSLinkTime
                                        = stApsDsflowNv.ulDSTotalLinkTime;

        pstApsDsFlowCtx->astApsDsFlowStats[0].stTotalFlowInfo.ulDSReceiveFluxHigh
                                        = stApsDsflowNv.ulDSTotalReceiveFluxHigh;

        pstApsDsFlowCtx->astApsDsFlowStats[0].stTotalFlowInfo.ulDSReceiveFluxLow
                                        = stApsDsflowNv.ulDSTotalReceiveFluxLow;

        pstApsDsFlowCtx->astApsDsFlowStats[0].stTotalFlowInfo.ulDSSendFluxHigh
                                        = stApsDsflowNv.ulDSTotalSendFluxHigh;

        pstApsDsFlowCtx->astApsDsFlowStats[0].stTotalFlowInfo.ulDSSendFluxLow
                                        = stApsDsflowNv.ulDSTotalSendFluxLow;

    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_ClearDsFlowInfoInNv
 ��������  : ���NV���е���ʷ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_APS_ClearDsFlowInfoInNv( VOS_VOID )
{
    TAF_APS_DSFLOW_NV_STRU              stApsDsflowNv;

    /* ��ʼ�� */
    PS_MEM_SET(&stApsDsflowNv, 0, sizeof(TAF_APS_DSFLOW_NV_STRU));

    /* ˢ��NV�� */
    if (NV_OK != NV_Write(en_NV_Item_DSFLOW_REPORT, &stApsDsflowNv, sizeof(TAF_APS_DSFLOW_NV_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_ClearDsFlowInfoInNv:Write NVIM Failed");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SaveDsFlowInfoToNv
 ��������  : ������ʷ������Ϣ��NV��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��5��15��
    ��    ��   : A00165503
    �޸�����   : DTS2012051402688: Gģ�����������Ϣ�󲦺�����, ʱ��С��10��
                 ��, ��������ʱû�н�������Ϣд��NV
*****************************************************************************/
VOS_VOID  TAF_APS_SaveDsFlowInfoToNv( VOS_VOID )
{
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;
    TAF_APS_DSFLOW_NV_STRU              stApsDsflowNv;
    TAF_DSFLOW_QUERY_INFO_STRU          stDsFlowQryInfo;

    /* ��ʼ�� */
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();
    PS_MEM_SET(&stApsDsflowNv, 0, sizeof(TAF_APS_DSFLOW_NV_STRU));
    PS_MEM_SET(&stDsFlowQryInfo, 0, sizeof(TAF_DSFLOW_QUERY_INFO_STRU));

    if (VOS_TRUE == pstApsDsFlowCtx->ucDsFlowSave2NvFlg)
    {

        /* ��ȡ��ʷ������Ϣ�� */
        TAF_APS_QryAllRabDsFlowStats(&stDsFlowQryInfo);

        /* ˢ��������Ϣ���NV�� */
        stApsDsflowNv.ulDSLastLinkTime          = stDsFlowQryInfo.stCurrentFlowInfo.ulDSLinkTime;
        stApsDsflowNv.ulDSTotalLinkTime         = stDsFlowQryInfo.stTotalFlowInfo.ulDSLinkTime;
        stApsDsflowNv.ulDSTotalReceiveFluxHigh  = stDsFlowQryInfo.stTotalFlowInfo.ulDSReceiveFluxHigh;
        stApsDsflowNv.ulDSTotalReceiveFluxLow   = stDsFlowQryInfo.stTotalFlowInfo.ulDSReceiveFluxLow;
        stApsDsflowNv.ulDSTotalSendFluxHigh     = stDsFlowQryInfo.stTotalFlowInfo.ulDSSendFluxHigh;
        stApsDsflowNv.ulDSTotalSendFluxLow      = stDsFlowQryInfo.stTotalFlowInfo.ulDSSendFluxLow;

        /* дNV�� */
        if (NV_OK != NV_Write(en_NV_Item_DSFLOW_REPORT, &stApsDsflowNv, sizeof(TAF_APS_DSFLOW_NV_STRU)))
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SaveDsFlowInfoToNv: Write NVIM Failed");
        }
    }
    else
    {
        TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_APS_SaveDsFlowInfoToNv: Save2NvFlg is not set.");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ReadPdpActLimitFlgFromNv
 ��������  : ��en_NV_Item_PDP_Actving_Limit�ж�ȡPDP�������ޱ�־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��15��
    ��    ��   : M00217266
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID TAF_APS_ReadPdpActLimitFlgFromNv(VOS_VOID)
{
    TAF_APS_NVIM_PDP_ACT_LIMIT_STRU     stNvPdpActLimit;
    TAF_APS_PDP_ACT_LIMIT_INFO_STRU    *pstPdpActLimitInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    ulLength = 0;

    PS_MEM_SET(&stNvPdpActLimit, 0x00, sizeof(TAF_APS_NVIM_PDP_ACT_LIMIT_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_Pdp_Act_Limit_Para, &ulLength);
    if (ulLength > sizeof(stNvPdpActLimit))
    {
        return;
    }

    /* ��en_NV_Item_Pdp_Act_Limit_Para�ж�ȡPDP�������ޱ�־ */
    if (NV_OK !=  NV_Read(en_NV_Item_Pdp_Act_Limit_Para,
                          &stNvPdpActLimit,
                          ulLength))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_ReadPdpActLimitFlgFromNv:NVIM Read Failed");

        return;
    }

    /* PDP�������ޱ�־��Ч�Լ�� */
    if ((stNvPdpActLimit.ucNvimActiveFlg != VOS_TRUE)
     && (stNvPdpActLimit.ucNvimActiveFlg != VOS_FALSE))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_ReadPdpActLimitFlgFromNv:NVIM Is Anavil");
        return;
    }

    pstPdpActLimitInfo = TAF_APS_GetPdpActLimitInfoAddr();

    pstPdpActLimitInfo->ucPdpActLimitFlg = stNvPdpActLimit.ucNvimActiveFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ReadDsflowRateConfigFromNv
 ��������  : ��en_NV_Item_Dsflow_Rate_Config����������
 �������  : pstSwitchDdrInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��13��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��05��28��
    ��    ��   : m00217266
    �޸�����   : modify for adapt k3 aps profile
*****************************************************************************/
VOS_VOID TAF_APS_ReadDsflowRateConfigFromNv(TAF_APS_SWITCH_DDR_RATE_INFO_STRU *pstSwitchDdrInfo)
{
    TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU          stRateConfig;
    TAF_NV_MULTI_DFS_DSFLOW_RATE_CONFIG_STRU    stMultiDfsConfig;
    VOS_UINT32                                  ulIndex;

    PS_MEM_SET(&stRateConfig, 0, sizeof(TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU));
    PS_MEM_SET(&stMultiDfsConfig, 0, sizeof(TAF_NV_MULTI_DFS_DSFLOW_RATE_CONFIG_STRU));

    /* ��NV�ж�ȡ��������NV�� */
    if (NV_OK != NV_Read (en_NV_Item_Dfs_Dsflow_Rate_Config,
                          &stRateConfig, sizeof(TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_ReadDsflowRateConfigFromNv(): NV_Read en_NV_Item_Dsflow_Rate_Config Error");
        return;
    }

    if (NV_OK != NV_Read (en_NV_Item_Multi_Dfs_Dsflow_Rate_CFG,
                          &stMultiDfsConfig, sizeof(TAF_NV_MULTI_DFS_DSFLOW_RATE_CONFIG_STRU)))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_ReadDsflowRateConfigFromNv(): NV_Read en_NV_Item_Multi_Dfs_Dsflow_Rate_CFG Error");
        return;
    }

    if (0 == stMultiDfsConfig.astDfsConfig[0].ulProfileNum)
    {
        if (0 == stRateConfig.ulProfileNum)
        {
            PS_MEM_SET((VOS_VOID *)pstSwitchDdrInfo->astDfsConfig, 0, sizeof(TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU) * TAF_NVIM_DIFF_DFS_NUM);
            return;
        }

        pstSwitchDdrInfo->ulMultiDfsFlg = VOS_FALSE;

        TAF_APS_Recorrect_ProfileNum(&stRateConfig, 1);
        PS_MEM_CPY(&pstSwitchDdrInfo->astDfsConfig[0], &stRateConfig, sizeof(TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU));
    }
    else
    {
        pstSwitchDdrInfo->ulMultiDfsFlg = VOS_TRUE;

        TAF_APS_Recorrect_ProfileNum(stMultiDfsConfig.astDfsConfig, TAF_NVIM_DIFF_DFS_NUM);
        PS_MEM_CPY((VOS_VOID *)pstSwitchDdrInfo->astDfsConfig, (VOS_VOID *)stMultiDfsConfig.astDfsConfig, sizeof(TAF_NV_MULTI_DFS_DSFLOW_RATE_CONFIG_STRU));
    }

    /* NV�ĵ�һ��profile�������С��ddrƵ�� */
    pstSwitchDdrInfo->ulMinBand = pstSwitchDdrInfo->astDfsConfig[0].astProfile[0].ulDdrBand;

    /* NV�����һ��profile���������ddrƵ�� */
    ulIndex = pstSwitchDdrInfo->astDfsConfig[0].ulProfileNum - 1;
    pstSwitchDdrInfo->ulMaxBand = pstSwitchDdrInfo->astDfsConfig[0].astProfile[ulIndex].ulDdrBand;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_Recorrect_ProfileNum
 ��������  : ����profile�е��쳣num����
 �������  : TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU *pstDfsProfile
             VOS_UINT32 ulProfileNum
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��05��28��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_Recorrect_ProfileNum(
    TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU     *pstDfsProfile,
    VOS_UINT32                              ulProfileNum)
{
    VOS_UINT32                              i;
    TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU     *pstDfsProTemp;

    for (i = 0; i < ulProfileNum; i++)
    {
        pstDfsProTemp = pstDfsProfile + i;

        if (pstDfsProTemp->ulProfileNum > TAF_NVIM_DFS_MAX_PROFILE_NUM)
        {
            pstDfsProTemp->ulProfileNum = TAF_NVIM_DFS_MAX_PROFILE_NUM;
        }
    }

    return;
}


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_APS_ReadPktCdataInactivityTimeLenFromNv
 ��������  : ��NV�л�ȡMaxNoDataTimeLen
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��21��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_ReadPktCdataInactivityTimeLenFromNv(VOS_VOID)
{
    TAF_NVIM_CDATA_GENERIC_CONFIG_STRU   stCdataGenericConfig;

    PS_MEM_SET(&stCdataGenericConfig, 0 , sizeof(stCdataGenericConfig));

    if (NV_OK != NV_Read(en_NV_Item_CDATA_GENERIC_CONFIG, &stCdataGenericConfig, sizeof(stCdataGenericConfig)))
    {
        /*��ȡNV ʧ�ܣ�����Ĭ��ֵ */
        TAF_APS_SetPktCdataInactivityTimerLen(TAF_APS_PACKET_CDATA_INACTIVITY_TIME_LEN);

        return;
    }

    TAF_APS_LogReadNVInfo(en_NV_Item_CDATA_GENERIC_CONFIG,
                          sizeof(TAF_NVIM_CDATA_GENERIC_CONFIG_STRU),
                          WUEPS_PID_TAF,
                          (VOS_UINT8 *)&stCdataGenericConfig);

    TAF_APS_SetPktCdataInactivityTimerLen(stCdataGenericConfig.ucPktCdataInactivityTmrLen);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_Read1xDataSoCfg
 ��������  : ��NV�л�ȡ 1x ����ҵ���� SO ��ʼֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��8��10��
   ��    ��   : c00299063
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_Read1xDataSoCfgNvim(VOS_VOID)
{
    TAF_NVIM_1X_DATA_SO_CFG             st1xDataSoCfg;

    PS_MEM_SET(&st1xDataSoCfg, 0 , sizeof(st1xDataSoCfg));

    if (NV_OK != NV_Read(en_Nv_Item_1X_DATA_SO_CFG, &st1xDataSoCfg, sizeof(st1xDataSoCfg)))
    {
        /*��ȡNV ʧ�ܣ�����Ĭ��ֵ */
        TAF_APS_SetFsmCtxCdataSoInitType(TAF_APS_CDATA_SO_33_PPP_PKT_DATA);

        return;
    }

    if ((TAF_APS_CDATA_SO_33_PPP_PKT_DATA       != st1xDataSoCfg.usSo)
     && (TAF_APS_CDATA_SO_7_PPP_PKT_DATA_PRE707 != st1xDataSoCfg.usSo))
    {
       TAF_APS_SetFsmCtxCdataSoInitType(TAF_APS_CDATA_SO_33_PPP_PKT_DATA);
    }
    else
    {
       TAF_APS_SetFsmCtxCdataSoInitType(st1xDataSoCfg.usSo);
    }
}


/*****************************************************************************
 �� �� ��  : TAF_APS_ReadCdataDiscingParaCfgFromNv
 ��������  : ��NV�ж�ȡ���������еĲ���������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��4��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_ReadCdataDiscingParaCfgFromNv(VOS_VOID)
{
    NAS_NVIM_CDATA_DISCING_PARA_INFO_STRU   stCdataDiscingPara;

    PS_MEM_SET(&stCdataDiscingPara, 0 , sizeof(stCdataDiscingPara));

    if (NV_OK == NV_Read(en_NV_Item_CDATA_DISCING_PARA_CFG, &stCdataDiscingPara, sizeof(stCdataDiscingPara)))
    {
        /* ��ȡNV�ɹ� */
        TAF_APS_SetCdataPppDeactTimerLen(stCdataDiscingPara.ucPppDeactTimerLen);
    }
    else
    {
        TAF_APS_SetCdataPppDeactTimerLen(TI_TAF_APS_CDATA_DEFAULT_PPP_DEACT_LEN);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_ReadPppAuthInfoFromCardNv
 ��������  : ��ȡPPP��Ȩ�������û�������������Ƿ�����ap��nv��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��26��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_ReadPppAuthInfoFromCardNv( VOS_VOID )
{
    NAS_NVIM_PPP_AUTH_INFO_FROM_CARD_STRU                   stIsPppAuthGetFromCard;

    PS_MEM_SET(&stIsPppAuthGetFromCard, 0 , sizeof(stIsPppAuthGetFromCard));

    if (NV_OK == NV_Read(en_NV_Item_PPP_AUTH_INFO_FROM_CARD_FLAG, &stIsPppAuthGetFromCard, sizeof(stIsPppAuthGetFromCard)))
    {
        /* ��ȡNV�ɹ� */
        TAF_APS_SetPppAuthInfoGetFromCardFlag(stIsPppAuthGetFromCard.ulIsPppAuthGetFromCard);
    }
    else
    {
#ifdef DMT
        TAF_APS_SetPppAuthInfoGetFromCardFlag(VOS_TRUE);
#else
        TAF_APS_SetPppAuthInfoGetFromCardFlag(VOS_FALSE);
#endif
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ReadCdataEhrpdAutoAttachFlagFromNv
 ��������  : ��NV�ж�ȡEhrpd Auto Attach Flag
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��29��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_ReadCdataEhrpdAutoAttachFlagFromNv(VOS_VOID)
{
    NAS_NVIM_EHRPD_AUTO_ATTACH_CTRL_CFG_STRU      stAutoAttachFlag;

    if (NV_OK == NV_Read(en_NV_Item_EHRPD_AUTO_ATTACH_CTRL_CFG, &stAutoAttachFlag, sizeof(stAutoAttachFlag)))
    {
        TAF_APS_SetEhrpdAutoAttachFlag(stAutoAttachFlag.ucEnableFlag);
    }
    else
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_ReadCdataEhrpdAutoAttachFlagFromNv(): en_NV_Item_EHRPD_AUTO_ATTACH_CTRL_CFG read error");

        TAF_APS_SetEhrpdAutoAttachFlag(VOS_FALSE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ReadCdataUlNdisFilterVaildFlagFromNv
 ��������  : CDMA��򿪵�ʱ�򣬴�NV��ȡNDIS Filte��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��26��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_ReadCdataUlNdisFilterVaildFlagFromNv(VOS_VOID)
{
    TAF_NVIM_NDIS_FILTER_ENABLE_FLAG_CFG_STRU               stFilterEnableFlag;

    PS_MEM_SET(&stFilterEnableFlag, 0, sizeof(stFilterEnableFlag));

    if (NV_OK == NV_Read(en_NV_Item_NDIS_FILTER_ENABLE_FLAG_CFG, &stFilterEnableFlag, sizeof(stFilterEnableFlag)))
    {
        if (VOS_TRUE == stFilterEnableFlag.ucEnableFlag)
        {
            /* NVʹ�����IPF���˹��� */
            TAF_APS_SetUlNdisFilterValidFlag(TAF_APS_UL_NDIS_FILTER_VALID);
        }
        else
        {
            TAF_APS_SetUlNdisFilterValidFlag(TAF_APS_UL_NDIS_FILTER_INVALID);
        }
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_ReadCdataUlNdisFilterVaildFlagFromNv(): en_NV_Item_NDIS_FILTER_FLAG_CFG read error");

        TAF_APS_SetUlNdisFilterValidFlag(TAF_APS_UL_NDIS_FILTER_VALID);
    }

    return;
}

#endif

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_APS_ReadPdnTeardownPolicyNV
 ��������  : ��ȡPDN���ӶϿ�����������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��1��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_ReadPdnTeardownPolicyNV(VOS_VOID)
{
    TAF_NV_PDN_TEARDOWN_POLICY_STRU     stNvPdnPolicy;
    VOS_UINT32                          ulRslt;

    PS_MEM_SET(&stNvPdnPolicy, 0x00, sizeof(TAF_NV_PDN_TEARDOWN_POLICY_STRU));

    ulRslt = NV_Read(en_NV_Item_PDN_TEARDOWN_POLICY,
                &stNvPdnPolicy, sizeof(TAF_NV_PDN_TEARDOWN_POLICY_STRU));
    if (NV_OK == ulRslt)
    {
        TAF_APS_SetAllowDefPdnTeardownFlg(stNvPdnPolicy.ucAllowDefPdnTeardownFlg);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_ReadPdnTeardownPolicyNV: Read en_NV_Item_PDN_TEARDOWN_POLICY failed!");
    }

    return;
}
#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
