/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsDsFlowStats.c
  �� �� ��   : ����
  ��    ��   : o00132663
  ��������   : 2011��12��14��
  ����޸�   :
  ��������   : APS����ͳ�ƴ����ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��12��14��
    ��    ��   : o00132663
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafApsDsFlowStats.h"
#include "TafApsProcNvim.h"
#include "TafApsCtx.h"
#include "PsCommonDef.h"
#include "TafLog.h"
#include "ApsCdsInterface.h"
#include "TafApsSndAt.h"
#include "TafSdcLib.h"
#include "TafApsSndInternalMsg.h"

#include "NasUtranCtrlInterface.h"
#include "apminterface.h"

#include "TafApsComFunc.h"

#include "TafApsFsmMainTbl.h"

#include "TafApsMntn.h"
#include "TafApsProcEpdszid.h"

#include "TafApsCtx.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "cnas_cttf_hrpd_pa_pif.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define THIS_FILE_ID PS_FILE_ID_TAF_APS_DSFLOWSTATS_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/



/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_APS_StartDsFlowStats
 ��������  : PDP����ʱ�������RAB��������ͳ��
 �������  : ucRabId - RAB����ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��5��30��
    ��    ��   : zhangyizhan 60575
    �޸�����   : DTS2012052907939, ���浽NV��ʱ����NV 9036����
  3.��    ��   : 2012��11��09��
    ��    ��   : l00198894
    �޸�����   : Probe·�⹤�߶Խ���Ŀ����PDP���������ϱ���ʱ��
  4.��    ��   : 2012��12��26��
    ��    ��   : m00217266
    �޸�����   : DSDA C����ĿCDS�ӿ��޸�
  5.��    ��   : 2013��11��21��
    ��    ��   : j00174725
    �޸�����   : ROTS �޸�
*****************************************************************************/
VOS_VOID  TAF_APS_StartDsFlowStats(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          ulIndex;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;
    VOS_UINT16                          usModemid;

    /* �ж�RAB ID�Ƿ���Ч */
    if ((ucRabId < TAF_APS_RAB_ID_MIN)
     || (ucRabId > TAF_APS_RAB_ID_MAX))
    {
        return;
    }

    /* ��ʼ�� */
    ulIndex         = ucRabId - TAF_APS_RAB_ID_OFFSET;
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* ���RAB�Ƿ��Ѿ����� */
    if (VOS_TRUE == pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag)
    {
        TAF_NORMAL_LOG1(WUEPS_PID_TAF, "TAF_APS_StartDsFlowStats:NORMAL:RABM is already active! RABID:", ucRabId);
        return;
    }

    /*�ø�RABID�����־:*/
    pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag = VOS_TRUE;

    /* ����CDS API �����RABID����ʷ���� */
    usModemid = VOS_GetModemIDFromPid(WUEPS_PID_TAF);
    CDS_ClearBearerDataFlowInfo(ucRabId, usModemid);


    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
    /* ��ʼ��APS��ǰ����������ϢΪ0 */
    PS_MEM_SET(&pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo,
                0,
                sizeof(TAF_DSFLOW_INFO_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
    /* ��¼��ǰ���ӿ�ʼʱ�� */
    pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ulStartLinkTime = VOS_GetTick() / PRE_SECOND_TO_TICK;

    /* ���������ϱ���ʱ�� */
    TAF_APS_StartDsFlowRpt();

    /* �����Ҫ���浽NV���У����������Ա���������NV��ʱ�� */
    if (VOS_TRUE == pstApsDsFlowCtx->ucDsFlowSave2NvFlg)
    {
        TAF_APS_StartTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                           (pstApsDsFlowCtx->ucDsFlowSavePeriod * 60 * TIMER_S_TO_MS_1000),
                           TAF_APS_INVALID_PDPID);
    }
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_StopDsFlowStats
 ��������  : PDPȥ����ʱֹͣ���RAB��������ͳ��
 �������  : ucRabId - RAB����ID
 �������  : ��
 �� �� ֵ  : ��
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
  3.��    ��   : 2012��5��18��
    ��    ��   : A00165503
    �޸�����   : DTS2012041107552: Gģ����ʱ�����Ͽ�����, ����ͳ���쳣
  4.��    ��   : 2012��6��15��
    ��    ��   : f00179208
    �޸�����   : DTS2012061407364, ����ͳ�Ƶ�λ��������Χ��Ҫ��λ
  5.��    ��   : 2012��12��26��
    ��    ��   : m00217266
    �޸�����   : DSDA C����ĿCDS�ӿ��޸�
*****************************************************************************/
VOS_VOID  TAF_APS_StopDsFlowStats(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          ulIndex;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
    TAF_DSFLOW_INFO_STRU                stCurrentFlowInfo;
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
    VOS_UINT16                          usModemid;

    /* �ж�RAB ID�Ƿ���Ч */
    if ((ucRabId < TAF_APS_RAB_ID_MIN) || (ucRabId > TAF_APS_RAB_ID_MAX))
    {
        return;
    }

    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
    /* ��ʼ�� */
    PS_MEM_SET(&stCurrentFlowInfo, 0, sizeof(TAF_DSFLOW_INFO_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();
    ulIndex         = ucRabId - TAF_APS_RAB_ID_OFFSET;

    if (VOS_TRUE == pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag)
    {
        /* ˢ�����������ĵ�ǰ����������Ϣ */
        TAF_APS_GetCurrentFlowInfo(ucRabId, &stCurrentFlowInfo);
        pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo = stCurrentFlowInfo;

        /* ˢ�������������ۻ�����������Ϣ */
        pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSLinkTime
                        += pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSLinkTime;

        /* �����ֽ��ۼ� */
        TAF_APS_BIT64_ADD(pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSReceiveFluxHigh,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSReceiveFluxLow,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSReceiveFluxHigh,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSReceiveFluxLow,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSReceiveFluxHigh,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSReceiveFluxLow);

        /* �����ֽ��ۼ� */
        TAF_APS_BIT64_ADD(pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSSendFluxHigh,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSSendFluxLow,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSSendFluxHigh,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSSendFluxLow,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSSendFluxHigh,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSSendFluxLow);

        /* ���ø�RAB IDΪȥ�����־ */
        pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag = VOS_FALSE;

    }

    /* �����ǰ����RAB����ȥ�����ֹͣ�����ϱ���ʱ���������Ա���������ʱ�� */
    if (VOS_FALSE == TAF_APS_CheckIfActiveRabIdExist())
    {
        /* ���������ʷ������NV����ʹ�ܣ�дNV */
        TAF_APS_SaveDsFlowInfoToNv();

        TAF_APS_ReleaseDfs();

        TAF_APS_StopTimer(TI_TAF_APS_DSFLOW_REPORT,
                          TAF_APS_INVALID_PDPID);


        TAF_APS_StopTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                          TAF_APS_INVALID_PDPID);
    }

    /* ����CDS API �����RABID��������Ϣ */
    usModemid = VOS_GetModemIDFromPid(WUEPS_PID_TAF);
    CDS_ClearBearerDataFlowInfo(ucRabId, usModemid);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_QryDsFlowStats
 ��������  : ��ѯָ��RAB���ص�������Ϣ
 �������  : ucRabId          - RAB����ID
 �������  : pstDsFlowQryInfo - ������ѯ��Ϣָ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
*****************************************************************************/
/* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
VOS_VOID  TAF_APS_QryDsFlowStats(
    TAF_DSFLOW_QUERY_INFO_STRU         *pstDsFlowQryInfo,
    VOS_UINT8                           ucRabId
)
/* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
{
    VOS_UINT32                          ulIndex;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;

    /* ��ȡ����ͳ�������� */
    ulIndex         = ucRabId - TAF_APS_RAB_ID_OFFSET;
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* ˢ�¸�RAB ID��ǰ������Ϣ */
    TAF_APS_GetCurrentFlowInfo(ucRabId, &pstDsFlowQryInfo->stCurrentFlowInfo);

    /* ˢ�¸�RAB ID����ʷ������Ϣ */
    if (VOS_TRUE == pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag)
    {
        /* ������� */
        /* RABID��ʷ����     = APS����ͳ�������ı������ʷ���� + RABID��ǰ���� */
        /* RABID��ʷ����ʱ�� = APS����ͳ�������ı������ʷ����ʱ�� + RABID��ǰ����ʱ�� */

        TAF_APS_BIT64_ADD(pstDsFlowQryInfo->stTotalFlowInfo.ulDSReceiveFluxHigh,
                          pstDsFlowQryInfo->stTotalFlowInfo.ulDSReceiveFluxLow,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSReceiveFluxHigh,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSReceiveFluxLow,
                          pstDsFlowQryInfo->stCurrentFlowInfo.ulDSReceiveFluxHigh,
                          pstDsFlowQryInfo->stCurrentFlowInfo.ulDSReceiveFluxLow);

        TAF_APS_BIT64_ADD(pstDsFlowQryInfo->stTotalFlowInfo.ulDSSendFluxHigh,
                          pstDsFlowQryInfo->stTotalFlowInfo.ulDSSendFluxLow,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSSendFluxHigh,
                          pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSSendFluxLow,
                          pstDsFlowQryInfo->stCurrentFlowInfo.ulDSSendFluxHigh,
                          pstDsFlowQryInfo->stCurrentFlowInfo.ulDSSendFluxLow);

        pstDsFlowQryInfo->stTotalFlowInfo.ulDSLinkTime = pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo.ulDSLinkTime
                          + pstDsFlowQryInfo->stCurrentFlowInfo.ulDSLinkTime;

    }
    else
    {
        /* ���δ���� */
        /* RABID��ʷ���� = APS����ͳ�������ı������ʷ���� */

        pstDsFlowQryInfo->stTotalFlowInfo = pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stTotalFlowInfo;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_QryAllRabDsFlowStats
 ��������  : ��ѯ����RAB���ص�������Ϣ
 �������  : ��
 �������  : pstDsFlowQryInfo - ������ѯ��Ϣ�ṹָ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��16��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��3��26��
    ��    ��   : l60609
    �޸�����   : DTS2012032202846��IPV4V6�����������ʱ��Ϊ���ֵ�������ۼ�ֵ
*****************************************************************************/
/* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
VOS_VOID  TAF_APS_QryAllRabDsFlowStats(
    TAF_DSFLOW_QUERY_INFO_STRU          *pstTotalDsFlowQryInfo
)
/* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
{
    VOS_UINT8                           ucRabId;
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
    TAF_DSFLOW_QUERY_INFO_STRU      stDsFlowQryInfo;

    /* ������ѯ����RABID����ȡ������Ϣ���ۼ� */
    for ( ucRabId = TAF_APS_RAB_ID_MIN; ucRabId <=  TAF_APS_RAB_ID_MAX; ucRabId++ )
    {
        PS_MEM_SET(&stDsFlowQryInfo, 0, sizeof(TAF_DSFLOW_QUERY_INFO_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
        TAF_APS_QryDsFlowStats(&stDsFlowQryInfo, ucRabId);

        /* ��ǰ����ʱ��: ȡ��RAB�����ֵ */
        if (pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSLinkTime < stDsFlowQryInfo.stCurrentFlowInfo.ulDSLinkTime)
        {
            pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSLinkTime = stDsFlowQryInfo.stCurrentFlowInfo.ulDSLinkTime;
        }

        /* ��ǰ���ӽ����ֽ��ۼ� */
        TAF_APS_BIT64_ADD(pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSReceiveFluxHigh,
                          pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSReceiveFluxLow,
                          pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSReceiveFluxHigh,
                          pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSReceiveFluxLow,
                          stDsFlowQryInfo.stCurrentFlowInfo.ulDSReceiveFluxHigh,
                          stDsFlowQryInfo.stCurrentFlowInfo.ulDSReceiveFluxLow);

        /* ��ǰ���ӷ����ֽ��ۼ� */
        TAF_APS_BIT64_ADD(pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSSendFluxHigh,
                          pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSSendFluxLow,
                          pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSSendFluxHigh,
                          pstTotalDsFlowQryInfo->stCurrentFlowInfo.ulDSSendFluxLow,
                          stDsFlowQryInfo.stCurrentFlowInfo.ulDSSendFluxHigh,
                          stDsFlowQryInfo.stCurrentFlowInfo.ulDSSendFluxLow);

        /* ������ʱ���ۼ�: ȡ��RAB�����ֵ */
        if (pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSLinkTime < stDsFlowQryInfo.stTotalFlowInfo.ulDSLinkTime)
        {
            pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSLinkTime = stDsFlowQryInfo.stTotalFlowInfo.ulDSLinkTime;
        }

        /* �����ӽ����ֽ��ۼ� */
        TAF_APS_BIT64_ADD(pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSReceiveFluxHigh,
                          pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSReceiveFluxLow,
                          pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSReceiveFluxHigh,
                          pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSReceiveFluxLow,
                          stDsFlowQryInfo.stTotalFlowInfo.ulDSReceiveFluxHigh,
                          stDsFlowQryInfo.stTotalFlowInfo.ulDSReceiveFluxLow);

        /* �����ӷ����ֽ��ۼ� */
        TAF_APS_BIT64_ADD(pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSSendFluxHigh,
                          pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSSendFluxLow,
                          pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSSendFluxHigh,
                          pstTotalDsFlowQryInfo->stTotalFlowInfo.ulDSSendFluxLow,
                          stDsFlowQryInfo.stTotalFlowInfo.ulDSSendFluxHigh,
                          stDsFlowQryInfo.stTotalFlowInfo.ulDSSendFluxLow);

    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_ClearDsFlowStats
 ��������  : ���ָ��RAB���ص�������Ϣ
 �������  : ucRabId          - RAB����ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��26��
    ��    ��   : m00217266
    �޸�����   : DSDA C����ĿCDS�ӿ��޸�
  3.��    ��   : 2013��11��21��
    ��    ��   : j00174725
    �޸�����   : ROTS �޸�
*****************************************************************************/
VOS_VOID  TAF_APS_ClearDsFlowStats(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucRabActiveFlag;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;
    VOS_UINT16                          usModemid;


    /* ��ʼ�� */
    ulIndex         = ucRabId - TAF_APS_RAB_ID_OFFSET;
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* �ȱ����RABID�����־ */
    ucRabActiveFlag = pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag;

    /* ����ͳ��������ָ��RABID������Ϣ���� */
    PS_MEM_SET(&pstApsDsFlowCtx->astApsDsFlowStats[ulIndex],
                0,
                sizeof(TAF_APS_DSFLOW_STATS_STRU));

    /* �ָ���RABID�����־��Ϣ */
    pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag = ucRabActiveFlag;

    /* ���RAB�Ѽ������ǰ����ʱ����Ϊ��ǰʱ�䣬ͬʱ֪ͨCDS���������Ϣ */
    if (VOS_TRUE == ucRabActiveFlag)
    {
        /* ����CDS API �����RABID��������Ϣ */
        usModemid = VOS_GetModemIDFromPid(WUEPS_PID_TAF);
        CDS_ClearBearerDataFlowInfo(ucRabId, usModemid);

        /* ��¼��ǰ���ӿ�ʼʱ�� */
        pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ulStartLinkTime = VOS_GetTick() / PRE_SECOND_TO_TICK;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ClearAllRabDsFlowStats
 ��������  : �������RAB���ص�������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_APS_ClearAllRabDsFlowStats( VOS_VOID )
{
    VOS_UINT8                           ucRabId;

    /* ������ѯ����RABID�����������Ϣ */
    for ( ucRabId = TAF_APS_RAB_ID_MIN; ucRabId <=  TAF_APS_RAB_ID_MAX; ucRabId++ )
    {
        TAF_APS_ClearDsFlowStats(ucRabId);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_StartDsFlowRpt
 ��������  : ����APS�����ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��11��09��
    ��    ��   : l00198894
    �޸�����   : Probe·�⹤�߶Խ���Ŀȡ���޸������ϱ���־λ
*****************************************************************************/
VOS_VOID  TAF_APS_StartDsFlowRpt( VOS_VOID )
{
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;

    /* �����ǰ�����ϱ���ʱ���������У���ֹͣ��ʱ�� */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_DSFLOW_REPORT,
                                           TAF_APS_INVALID_PDPID);
    if (TAF_APS_TIMER_STATUS_RUNING == enTimerStatus)
    {
        TAF_APS_StopTimer(TI_TAF_APS_DSFLOW_REPORT, TAF_APS_INVALID_PDPID);
    }

    /* �жϵ�ǰ�Ƿ���RAB���� */
    if (VOS_TRUE == TAF_APS_CheckIfActiveRabIdExist())
    {
        /* ������ѯ����RABID��ˢ���Ѽ���RAB�ĵ�ǰ����������Ϣ */
        TAF_APS_UpdateAllRabCurrentFlowInfo();

        /* ���������ϱ���ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_DSFLOW_REPORT,
                           TI_TAF_APS_DSFLOW_REPORT_LEN,
                           TAF_APS_INVALID_PDPID);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_StopDsFlowRpt
 ��������  : ֹͣAPS�����ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��11��09��
    ��    ��   : l00198894
    �޸�����   : Probe·�⹤�߶Խ���Ŀȡ���޸������ϱ���־λ
*****************************************************************************/
VOS_VOID  TAF_APS_StopDsFlowRpt( VOS_VOID )
{
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;

    /* �����ǰ�����ϱ���ʱ���������У�ֹͣ��ʱ�� */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_DSFLOW_REPORT,
                                           TAF_APS_INVALID_PDPID);
    if (TAF_APS_TIMER_STATUS_RUNING == enTimerStatus)
    {
        TAF_APS_StopTimer(TI_TAF_APS_DSFLOW_REPORT, TAF_APS_INVALID_PDPID);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_QryDsFlowReportInfo
 ��������  : ��ѯָ��RAB���ص������ϱ���Ϣ
 �������  : ucRabId            - RAB����ID
 �������  : pstDsFlowRptInfo   - �����ϱ��ṹָ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_QryDsFlowReportInfo(
    VOS_UINT8                           ucRabId,
    TAF_DSFLOW_REPORT_STRU             *pstDsFlowRptInfo
)
{
    VOS_UINT32                          ulIndex;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
    TAF_DSFLOW_INFO_STRU                stCurrentFlowInfo;
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

    /* �ж�RAB ID�Ƿ���Ч */
    if ((ucRabId < TAF_APS_RAB_ID_MIN) || (ucRabId > TAF_APS_RAB_ID_MAX))
    {
        return;
    }

    /* ��ʼ�� */
    ulIndex         = ucRabId - TAF_APS_RAB_ID_OFFSET;
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
    PS_MEM_SET(&stCurrentFlowInfo, 0, sizeof(TAF_DSFLOW_INFO_STRU));
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

    /* ��ȡ����ͳ�������� */
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* ��ȡ��ǰ����������Ϣ */
    TAF_APS_GetCurrentFlowInfo(ucRabId, &stCurrentFlowInfo);
    pstDsFlowRptInfo->stCurrentFlowInfo = stCurrentFlowInfo;

    /* �������ʣ�(��ʱ����ʱʱ�ĵ�ǰ���ӽ������� - ��ʱ������ʱ�ĵ�ǰ���ӽ������� )/��ʱ������ */
    TAF_APS_CalcDsflowRate(pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSReceiveFluxHigh,
                           pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSReceiveFluxLow,
                           pstDsFlowRptInfo->stCurrentFlowInfo.ulDSReceiveFluxHigh,
                           pstDsFlowRptInfo->stCurrentFlowInfo.ulDSReceiveFluxLow,
                           (TI_TAF_APS_DSFLOW_REPORT_LEN/TIMER_S_TO_MS_1000),
                          &pstDsFlowRptInfo->ulCurrentReceiveRate);

    /* �������ʣ�(��ʱ����ʱʱ�ĵ�ǰ���ӷ������� - ��ʱ������ʱ�ĵ�ǰ���ӷ������� )/��ʱ������ */
    TAF_APS_CalcDsflowRate(pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSSendFluxHigh,
                           pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo.ulDSSendFluxLow,
                           pstDsFlowRptInfo->stCurrentFlowInfo.ulDSSendFluxHigh,
                           pstDsFlowRptInfo->stCurrentFlowInfo.ulDSSendFluxLow,
                           (TI_TAF_APS_DSFLOW_REPORT_LEN/TIMER_S_TO_MS_1000),
                          &pstDsFlowRptInfo->ulCurrentSendRate);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_QryAllRabDsFlowReportInfo
 ��������  : ��ѯ����RAB���ص������ϱ���Ϣ
 �������  : ��
 �������  : pstTotalDsFlowRptInfo   - �����ϱ��ṹָ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_QryAllRabDsFlowReportInfo(
    TAF_DSFLOW_REPORT_STRU             *pstTotalDsFlowRptInfo
)
{
    VOS_UINT8                           ucRabId;
    VOS_UINT32                          ulIndex;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;
    TAF_DSFLOW_REPORT_STRU              stDsFlowRptInfo;

    /* ��ȡ����ͳ�������� */
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* �����м����RAB���أ����β�ѯ�����ϱ���Ϣ */
    for ( ucRabId = TAF_APS_RAB_ID_MIN; ucRabId <=  TAF_APS_RAB_ID_MAX; ucRabId++ )
    {
        ulIndex         = ucRabId - TAF_APS_RAB_ID_OFFSET;

        if (VOS_TRUE == pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag)
        {
            /* ��ѯǰ�ȳ�ʼ��Ϊ0 */
            PS_MEM_SET(&stDsFlowRptInfo, 0, sizeof(TAF_DSFLOW_REPORT_STRU));

            /* ��ȡָ��RAB�������ϱ���Ϣ */
            TAF_APS_QryDsFlowReportInfo(ucRabId, &stDsFlowRptInfo);

            /* ��ǰ����ʱ��: ȡ��RAB�����ֵ */
            if (pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSLinkTime < stDsFlowRptInfo.stCurrentFlowInfo.ulDSLinkTime)
            {
                pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSLinkTime = stDsFlowRptInfo.stCurrentFlowInfo.ulDSLinkTime;
            }

            /* ��ǰ�������ʣ���ǰ�������ʣ���ǰ���ӷ�����������ǰ���ӽ������� :�ۼ� */
            pstTotalDsFlowRptInfo->ulCurrentReceiveRate += stDsFlowRptInfo.ulCurrentReceiveRate;
            pstTotalDsFlowRptInfo->ulCurrentSendRate    += stDsFlowRptInfo.ulCurrentSendRate;

            TAF_APS_BIT64_ADD(pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSReceiveFluxHigh,
                              pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSReceiveFluxLow,
                              pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSReceiveFluxHigh,
                              pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSReceiveFluxLow,
                              stDsFlowRptInfo.stCurrentFlowInfo.ulDSReceiveFluxHigh,
                              stDsFlowRptInfo.stCurrentFlowInfo.ulDSReceiveFluxLow);

            TAF_APS_BIT64_ADD(pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSSendFluxHigh,
                              pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSSendFluxLow,
                              pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSSendFluxHigh,
                              pstTotalDsFlowRptInfo->stCurrentFlowInfo.ulDSSendFluxLow,
                              stDsFlowRptInfo.stCurrentFlowInfo.ulDSSendFluxHigh,
                              stDsFlowRptInfo.stCurrentFlowInfo.ulDSSendFluxLow);

        }


    }

    /* ���ݲ�Ʒ��Ҫ�󣬱�����Q��ʵ��һ�£�QOSЭ�̷������ʣ�QOSЭ�̽�������: ȡ0 */
    pstTotalDsFlowRptInfo->ulQosReceiveRate = 0;
    pstTotalDsFlowRptInfo->ulQosSendRate    = 0;

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_GetCurrentFlowInfo
 ��������  : ��ȡָ��RABID�ĵ�ǰ����������Ϣ
 �������  : ucRabId          - RAB����ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��26��
    ��    ��   : m00217266
    �޸�����   : DSDA C����ĿCDS�ӿ��޸�(CDS_GetBearerDataFlowInfo���modemid)
  3.��    ��   : 2013��07��222��
    ��    ��   : j00177245
    �޸�����   : ����Coverity
  4.��    ��   : 2013��11��21��
    ��    ��   : j00174725
    �޸�����   : ROTS �޸�
*****************************************************************************/
/* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
VOS_VOID  TAF_APS_GetCurrentFlowInfo(
    VOS_UINT8                           ucRabId,
    TAF_DSFLOW_INFO_STRU               *pstCurrentFlowInfo
)
/* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
{
    CDS_BEARER_DATA_FLOW_STRU           stDataFlowInfo;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulCurSysTime;
    VOS_UINT16                          usModemid;

    if (ucRabId < TAF_APS_RAB_ID_OFFSET)
    {
        ucRabId = TAF_APS_RAB_ID_OFFSET;
    }

    /* ��ʼ�� */
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();
    ulIndex         = ucRabId - TAF_APS_RAB_ID_OFFSET;

    /* ������� */
    /* ����CDS API CDS_GetBearerDataFlowInfo��ȡ��ǰ�������� */
    /* RABID��ǰ���� = CDS���صĵ�ǰ�������� */

    /* ���δ���� */
    /* RABID��ǰ���� = APS����ͳ�������ı���ĵ�ǰ�������� */

    if (ulIndex >= TAF_APS_MAX_RAB_NUM)
    {
        ulIndex = TAF_APS_MAX_RAB_NUM - 1;
    }

    /* ��ȡָ��RABID�ĵ�ǰ����������Ϣ */
    if (VOS_TRUE == pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag)
    {
        /* ������Ϣ��ʼ�� */
        PS_MEM_SET(&stDataFlowInfo, 0, sizeof(CDS_BEARER_DATA_FLOW_STRU));

        usModemid = VOS_GetModemIDFromPid(WUEPS_PID_TAF);
        CDS_GetBearerDataFlowInfo(ucRabId, &stDataFlowInfo, usModemid);

        /* ˢ�����������ĵ�ǰ����������Ϣ */
        pstCurrentFlowInfo->ulDSReceiveFluxHigh
                                    = stDataFlowInfo.ulTotalReceiveFluxHigh;

        pstCurrentFlowInfo->ulDSReceiveFluxLow
                                    = stDataFlowInfo.ulTotalReceiveFluxLow;

        pstCurrentFlowInfo->ulDSSendFluxHigh
                                    = stDataFlowInfo.ulTotalSendFluxHigh;

        pstCurrentFlowInfo->ulDSSendFluxLow
                                    = stDataFlowInfo.ulTotalSendFluxLow;

        /* ��ǰ����ʱ�䣺��ǰʱ��-PDP����ʱ�� */
        ulCurSysTime = VOS_GetTick() / PRE_SECOND_TO_TICK;

        /*��ṹ���п�ʼ����ʱ�����㣬�õ�����������ʱ��:*/
        if ( VOS_OK != TAF_CalcTime(pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ulStartLinkTime,
                                    ulCurSysTime,
                                    &pstCurrentFlowInfo->ulDSLinkTime) )
        {
            /*��ӡ������Ϣ---�������һ��DS�ӿ�ʼ���ӵ�������������ʱ��(����)ʱ����:*/
            TAF_WARNING_LOG1( WUEPS_PID_TAF,
                              "TAF_APS_UpdateCurrentFlowInfo:WARNING:TAF_CalcTime FAIL! RabId:",
                              ucRabId );
        }

    }
    else
    {
        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
        PS_MEM_CPY(pstCurrentFlowInfo,
                  &pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo,
                   sizeof(TAF_DSFLOW_INFO_STRU) );
        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_UpdateAllRabCurrentFlowInfo
 ��������  : ˢ�������Ѽ����RABID�ĵ�ǰ����������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_APS_UpdateAllRabCurrentFlowInfo( VOS_VOID )
{
    VOS_UINT8                           ucRabId;
    VOS_UINT32                          ulIndex;
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
    TAF_DSFLOW_INFO_STRU                stCurrentFlowInfo;
    /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;

    /* ��ȡ����ͳ��������ָ�� */
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* ������ѯ����RABID��ˢ�µ�ǰ����������Ϣ */
    for ( ucRabId = TAF_APS_RAB_ID_MIN; ucRabId <=  TAF_APS_RAB_ID_MAX; ucRabId++ )
    {
        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
        /* ��ʼ�� */
        PS_MEM_SET(&stCurrentFlowInfo, 0, sizeof(TAF_DSFLOW_INFO_STRU));
        /* Modified by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

        /* ��ȡ��ǰ����������Ϣ */
        TAF_APS_GetCurrentFlowInfo(ucRabId, &stCurrentFlowInfo);

        /* ˢ������ͳ�������ĵ�ǰ������Ϣ */
        ulIndex                         = ucRabId - TAF_APS_RAB_ID_OFFSET;
        pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].stCurrentFlowInfo
                                        = stCurrentFlowInfo;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_UpdateAllRabCurrentFlowInfo
 ��������  : ��鵱ǰ�Ƿ���RABID���ڼ���̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_APS_CheckIfActiveRabIdExist( VOS_VOID )
{
    VOS_UINT8                           ucRabId;
    VOS_UINT32                          ulIndex;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx;

    /* ��ʼ�� */
    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* ������ѯ����RABID��ˢ�µ�ǰ����������Ϣ */
    for ( ucRabId = TAF_APS_RAB_ID_MIN; ucRabId <=  TAF_APS_RAB_ID_MAX; ucRabId++ )
    {
        ulIndex     = ucRabId - TAF_APS_RAB_ID_OFFSET;

        if (VOS_TRUE == pstApsDsFlowCtx->astApsDsFlowStats[ulIndex].ucRabActiveFlag)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_CalcDsflowRate
 ��������  : ������������ʵ�ֺ���
 �������  : ulStartHigh - ����������ʼֵ���ֽ�
             ulStartLow  - ����������ʼֵ���ֽ�
             ulEndHigh   - ����������ֵֹ���ֽ�
             ulEndLow    - ����������ֵֹ���ֽ�
 �������  : pulRate     - ��������ָ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��15��
    ��    ��   : ŷ���� 00132663
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_APS_CalcDsflowRate(
    VOS_UINT32                          ulStartHigh,
    VOS_UINT32                          ulStartLow,
    VOS_UINT32                          ulEndHigh,
    VOS_UINT32                          ulEndLow,
    VOS_UINT32                          ulPeriod,
    VOS_UINT32                         *pulRate
)
{
    VOS_UINT32                          ulSubRstHigh;       /* ����������ֽ� */
    VOS_UINT32                          ulSubRstLow;        /* ����������ֽ� */
    VOS_UINT32                          ulQuotientHigh;     /* ����������ֽ� */
    VOS_UINT32                          ulQuotientLow;      /* ����������ֽ� */
    VOS_UINT32                          ulRemainder;        /* ����������� */
    VOS_UINT32                          ulResult;


    /* ��������ֵ */
    TAF_APS_BIT64_SUB(ulSubRstHigh,
                      ulSubRstLow,
                      ulEndHigh,
                      ulEndLow,
                      ulStartHigh,
                      ulStartLow);

    /* �������� */
    ulResult = VOS_64Div32(ulSubRstHigh,
                           ulSubRstLow,
                           ulPeriod,
                          &ulQuotientHigh,
                          &ulQuotientLow,
                          &ulRemainder);

    if ( VOS_OK != ulResult )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_APS_CalcDsflowRate: VOS_64Div32 return error.");

        *pulRate = 0;
        return;
    }

    /*Ŀǰ�Ĵ����ٶȲ������4GB/s����ulQuotientHighΪ0��
      ֻ�����̵ĵ�32λulQuotientLow������: */
    *pulRate = ulQuotientLow;

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_ClearApDsFlowStats
 ��������  : ���������ֵͳ����Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��2��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_ClearApDsFlowStats( VOS_VOID )
{
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstDsFlowCtx = VOS_NULL_PTR;

    pstDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    pstDsFlowCtx->ulTotalFluxHigh = 0;
    pstDsFlowCtx->ulTotalFluxLow  = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ProcApDsFlowRpt
 ��������  : ����������ֵ�ϱ�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��2��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��2��
    ��    ��   : w00316404
    �޸�����   : clean coverity
*****************************************************************************/
VOS_VOID TAF_APS_ProcApDsFlowRpt(VOS_VOID)
{
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstDsflowCtx = VOS_NULL_PTR;
    TAF_APDSFLOW_REPORT_STRU            stApDsFlowRptInfo;
    TAF_DSFLOW_REPORT_STRU              stTotalDsFlowRptInfo;
    TAF_DSFLOW_QUERY_INFO_STRU          stDsFlowQryInfo;
    TAF_CTRL_STRU                       stCtrlHdr;
    VOS_UINT32                          ulTotalFluxThresHigh;
    VOS_UINT32                          ulTotalFluxThresLow;
    VOS_UINT32                          ulTotalFluxHigh;
    VOS_UINT32                          ulTotalFluxLow;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stApDsFlowRptInfo, 0x00, sizeof(TAF_APDSFLOW_REPORT_STRU));
    PS_MEM_SET(&stTotalDsFlowRptInfo, 0x00, sizeof(TAF_DSFLOW_REPORT_STRU));
    PS_MEM_SET(&stDsFlowQryInfo, 0x00, sizeof(TAF_DSFLOW_QUERY_INFO_STRU));
    PS_MEM_SET(&stCtrlHdr, 0x00, sizeof(TAF_CTRL_STRU));

    pstDsflowCtx = TAF_APS_GetDsFlowCtxAddr();

    if (VOS_TRUE == pstDsflowCtx->ulFluxThresRptFlg)
    {
        /* ��ѯ���м���RAB���ص��ϱ�������Ϣ */
        TAF_APS_QryAllRabDsFlowReportInfo(&stTotalDsFlowRptInfo);

        /* ��ѯ����RAB���ص�������Ϣ */
        TAF_APS_QryAllRabDsFlowStats(&stDsFlowQryInfo);

        /* �ۼ����������� */
        TAF_APS_BIT64_ADD(ulTotalFluxHigh,
                          ulTotalFluxLow,
                          stDsFlowQryInfo.stTotalFlowInfo.ulDSReceiveFluxHigh,
                          stDsFlowQryInfo.stTotalFlowInfo.ulDSReceiveFluxLow,
                          stDsFlowQryInfo.stTotalFlowInfo.ulDSSendFluxHigh,
                          stDsFlowQryInfo.stTotalFlowInfo.ulDSSendFluxLow);

        /* �����ۼ������ϱ���ֵ */
        TAF_APS_BIT64_ADD(ulTotalFluxThresHigh,
                          ulTotalFluxThresLow,
                          pstDsflowCtx->ulTotalFluxHigh,
                          pstDsflowCtx->ulTotalFluxLow,
                          pstDsflowCtx->ulFluxThresHigh,
                          pstDsflowCtx->ulFluxThresLow);

        /* ����Ƿ�ﵽ�����ϱ���ֵ */
        TAF_APS_BIT64_COMPARE(ulTotalFluxHigh,
                              ulTotalFluxLow,
                              ulTotalFluxThresHigh,
                              ulTotalFluxThresLow,
                              ulResult);

        if ((TAF_APS_BIT64_GREAT == ulResult) || (TAF_APS_BIT64_EQUAL == ulResult))
        {
            /* �����ۼ����� */
            pstDsflowCtx->ulTotalFluxHigh       = ulTotalFluxHigh;
            pstDsflowCtx->ulTotalFluxLow        = ulTotalFluxLow;

            /* ��д����ͷ */
            TAF_APS_CFG_AT_EVT_CTRL_HDR(&stCtrlHdr, MN_CLIENT_ID_BROADCAST, 0);

            /* ��д�¼����� */
            stApDsFlowRptInfo.ulCurrentTxRate   = stTotalDsFlowRptInfo.ulCurrentSendRate;
            stApDsFlowRptInfo.ulCurrentRxRate   = stTotalDsFlowRptInfo.ulCurrentReceiveRate;
            stApDsFlowRptInfo.stCurrentFlowInfo = stTotalDsFlowRptInfo.stCurrentFlowInfo;
            stApDsFlowRptInfo.stTotalFlowInfo   = stDsFlowQryInfo.stTotalFlowInfo;

            /* ������ֵ�ϱ� */
            TAF_APS_SndApDsFlowRptInd(&stCtrlHdr, &stApDsFlowRptInfo);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ShowDdrInfo
 ��������  : ��ӡDDR��Ƶ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��05��
    ��    ��   : ���� 00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_ShowDdrInfo(VOS_VOID)
{
    VOS_UINT32                              i;
    VOS_UINT32                              j;
    TAF_APS_SWITCH_DDR_RATE_INFO_STRU      *pstSwitchDdrInfo;

    pstSwitchDdrInfo = TAF_APS_GetSwitchDdrRateInfoAddr();

    /*vos_printf("request id                 %d\n", pstSwitchDdrInfo->iDfsReqId);*/
    (VOS_VOID)vos_printf("request id                 %d\n", pstSwitchDdrInfo->iDfsReqId);
    (VOS_VOID)vos_printf("request value              %d\n", pstSwitchDdrInfo->ulReqValue);
    (VOS_VOID)vos_printf("multi dfs flag             %d\n", pstSwitchDdrInfo->ulMultiDfsFlg);

    for (i = 0; i < TAF_NVIM_DIFF_DFS_NUM; i++)
    {
        for (j = 0; j < pstSwitchDdrInfo->astDfsConfig[i].ulProfileNum; j++)
        {
            (VOS_VOID)vos_printf("rat[%d] profile[%d] ulDlRate           %d\n", i, j, pstSwitchDdrInfo->astDfsConfig[i].astProfile[j].ulDlRate);
            (VOS_VOID)vos_printf("rat[%d] profile[%d] ulUlRate           %d\n", i, j, pstSwitchDdrInfo->astDfsConfig[i].astProfile[j].ulUlRate);
            (VOS_VOID)vos_printf("rat[%d] profile[%d] ulDdrBand          %d\n", i, j, pstSwitchDdrInfo->astDfsConfig[i].astProfile[j].ulDdrBand);
        }
    }

    (VOS_VOID)vos_printf("request Suc Count          %d\n", pstSwitchDdrInfo->stDfsDebugInfo.ulRequestSucCnt);
    (VOS_VOID)vos_printf("request fail Count         %d\n", pstSwitchDdrInfo->stDfsDebugInfo.ulRequestFailCnt);
    (VOS_VOID)vos_printf("update Suc Count           %d\n", pstSwitchDdrInfo->stDfsDebugInfo.ulUpdateSucCnt);
    (VOS_VOID)vos_printf("update fail count          %d\n", pstSwitchDdrInfo->stDfsDebugInfo.ulUpdateFailCnt);

    (VOS_VOID)vos_printf("min band                   %d\n", pstSwitchDdrInfo->ulMinBand);
    (VOS_VOID)vos_printf("max band                   %d\n", pstSwitchDdrInfo->ulMaxBand);

}

/*****************************************************************************
 �� �� ��  : TAF_APS_ReleaseDfs
 ��������  : �ͷ�DDR��Ƶ��ͶƱ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��05��
    ��    ��   : ���� 00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_ReleaseDfs(VOS_VOID)
{
#if defined(INSTANCE_1) || defined(INSTANCE_2)

#else
    TAF_APS_SWITCH_DDR_RATE_INFO_STRU      *pstSwitchDdrInfo;

    pstSwitchDdrInfo = TAF_APS_GetSwitchDdrRateInfoAddr();

    if (0 != TAF_APS_GET_DFS_PROFILE_NUM())
    {
        if (MDRV_OK != mdrv_pm_dfs_qos_update(DFS_QOS_ID_DDR_MINFREQ_E,
                                              pstSwitchDdrInfo->iDfsReqId,
                                              TAF_APS_GET_DSFLOW_RELEASE_DFS()))
        {
            TAF_APS_DFS_UPDATE_FAIL_CNT(1);
            TAF_APS_SndOmDfsInfo(pstSwitchDdrInfo);
            return;
        }

        pstSwitchDdrInfo->ulReqValue   = TAF_APS_GET_DSFLOW_RELEASE_DFS();
        pstSwitchDdrInfo->ulSetMaxFlag = VOS_FALSE;
        TAF_APS_DFS_UPDATE_SUCC_CNT(1);
        TAF_APS_SndOmDfsInfo(pstSwitchDdrInfo);

        (VOS_VOID)mdrv_pm_wake_unlock(PWRCTRL_SLEEP_DSFLOW);

    }
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_GetCurrRatMode
 ��������  : ��ȡ��ǰ�Ľ��뼼��ģʽ������td��w
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_APS_RAT_TYPE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��05��26��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_APS_DFS_TYPE_ENUM_UINT32 TAF_APS_GetCurrDfsMode(VOS_VOID)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enMmcApsRat;
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode;

    enMmcApsRat = TAF_APS_GetCurrPdpEntityRatType();

    if (TAF_APS_RAT_TYPE_GSM == enMmcApsRat)
    {
        return TAF_APS_DFS_TYPE_GSM;
    }

    if (TAF_APS_RAT_TYPE_LTE == enMmcApsRat)
    {
        return TAF_APS_DFS_TYPE_LTE;
    }

    if (TAF_APS_RAT_TYPE_WCDMA == enMmcApsRat)
    {
        enUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

        if (NAS_UTRANCTRL_UTRAN_MODE_FDD == enUtranMode)
        {
            return TAF_APS_DFS_TYPE_WCDMA;
        }

        if (NAS_UTRANCTRL_UTRAN_MODE_TDD == enUtranMode)
        {
            return TAF_APS_DFS_TYPE_TD_WCDMA;
        }
    }

    if ((TAF_APS_RAT_TYPE_1X == enMmcApsRat)
     || (TAF_APS_RAT_TYPE_HRPD == enMmcApsRat)
     || (TAF_APS_RAT_TYPE_EHRPD == enMmcApsRat))
    {
        return TAF_APS_DFS_TYPE_CDMA;
    }

    return TAF_APS_DFS_TYPE_BASE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_FindDfsReqValueByRat
 ��������  : ���ݽ��뼼������DDR��Ƶ����ֵ
 �������  : VOS_UINT32                          ulDLRate
             VOS_UINT32                          ulULRate
 �������  : VOS_UINT32                         *pulReqValue
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��05��26��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_FindDfsReqValueByRat(
    VOS_UINT32                         *pulReqValue,
    VOS_UINT32                          ulDLRate,
    VOS_UINT32                          ulULRate
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulDLReqValue;
    VOS_UINT32                          ulULReqValue;
    TAF_APS_DFS_TYPE_ENUM_UINT32        enDfsType;

    ulDLReqValue = TAF_APS_GET_DSFLOW_MIN_DDR_BAND();
    ulULReqValue = TAF_APS_GET_DSFLOW_MIN_DDR_BAND();
    enDfsType    = TAF_APS_GetCurrDfsMode();

    if (0 == TAF_APS_GET_MULTI_DFS_PROFILE_NUM(enDfsType))
    {
        ulRet = TAF_APS_FindDfsReqValue(pulReqValue, ulDLRate, ulULRate);
        return ulRet;
    }

    /* �����������ٶ�Ӧ��DDR��Ƶֵ */
    for (i = 0; i < (TAF_APS_GET_MULTI_DFS_PROFILE_NUM(enDfsType)); i++)
    {
        if (i == (TAF_APS_GET_MULTI_DFS_PROFILE_NUM(enDfsType) - 1))
        {
            ulDLReqValue = TAF_APS_GET_MULTI_DFS_PROFILE_DDR_BAND(enDfsType, i);
            break;
        }

        if ((ulDLRate >= TAF_APS_GET_MULTI_DFS_PROFILE_DL_RATE(enDfsType, i))
         && (ulDLRate < TAF_APS_GET_MULTI_DFS_PROFILE_DL_RATE(enDfsType, i + 1)))
        {
            ulDLReqValue = TAF_APS_GET_MULTI_DFS_PROFILE_DDR_BAND(enDfsType, i);
            break;
        }
    }

    /* �����������ٶ�Ӧ��DDR��Ƶֵ */
    for (i = 0; i < (TAF_APS_GET_MULTI_DFS_PROFILE_NUM(enDfsType)); i++)
    {
        if (i == (TAF_APS_GET_MULTI_DFS_PROFILE_NUM(enDfsType) - 1))
        {
            ulULReqValue = TAF_APS_GET_MULTI_DFS_PROFILE_DDR_BAND(enDfsType, i);
            break;
        }

        if ((ulULRate >= TAF_APS_GET_MULTI_DFS_PROFILE_UL_RATE(enDfsType, i))
         && (ulULRate < TAF_APS_GET_MULTI_DFS_PROFILE_UL_RATE(enDfsType, i + 1)))
        {
            ulULReqValue = TAF_APS_GET_MULTI_DFS_PROFILE_DDR_BAND(enDfsType, i);
            break;
        }
    }

    *pulReqValue = PS_MAX(ulDLReqValue, ulULReqValue);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_FindDfsReqValue
 ��������  : ����DDR��Ƶ����ֵ
 �������  : VOS_UINT32                          ulDLRate
             VOS_UINT32                          ulULRate
 �������  : VOS_UINT32                         *pulReqValue
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��05��
    ��    ��   : ���� 00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_FindDfsReqValue(
    VOS_UINT32                         *pulReqValue,
    VOS_UINT32                          ulDLRate,
    VOS_UINT32                          ulULRate
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulDLReqValue;
    VOS_UINT32                          ulULReqValue;

    ulDLReqValue = TAF_APS_GET_DSFLOW_MIN_DDR_BAND();
    ulULReqValue = TAF_APS_GET_DSFLOW_MIN_DDR_BAND();

    if (0 == TAF_APS_GET_DFS_PROFILE_NUM())
    {
        return VOS_ERR;
    }

    /* �����������ٶ�Ӧ��DDR��Ƶֵ */
    for (i = 0; i < (TAF_APS_GET_DFS_PROFILE_NUM()); i++)
    {
        if (i == (TAF_APS_GET_DFS_PROFILE_NUM() - 1))
        {
            ulDLReqValue = TAF_APS_GET_DFS_PROFILE_DDR_BAND(i);
            break;
        }

        if ((ulDLRate >= TAF_APS_GET_DFS_PROFILE_DL_RATE(i))
         && (ulDLRate < TAF_APS_GET_DFS_PROFILE_DL_RATE(i + 1)))
        {
            ulDLReqValue = TAF_APS_GET_DFS_PROFILE_DDR_BAND(i);
            break;
        }
    }

    /* �����������ٶ�Ӧ��DDR��Ƶֵ */
    for (i = 0; i < (TAF_APS_GET_DFS_PROFILE_NUM()); i++)
    {
        if (i == (TAF_APS_GET_DFS_PROFILE_NUM() - 1))
        {
            ulULReqValue = TAF_APS_GET_DFS_PROFILE_DDR_BAND(i);
            break;
        }

        if ((ulULRate >= TAF_APS_GET_DFS_PROFILE_UL_RATE(i))
         && (ulULRate < TAF_APS_GET_DFS_PROFILE_UL_RATE(i + 1)))
        {
            ulULReqValue = TAF_APS_GET_DFS_PROFILE_DDR_BAND(i);
            break;
        }
    }

    *pulReqValue = PS_MAX(ulDLReqValue, ulULReqValue);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SwitchDdrRateByCurrentRate
 ��������  : ���ݵ�ǰ����������������DDR��Ƶ��
 �������  : VOS_UINT32 ulDlRate
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��05��
    ��    ��   : ���� 00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_SwitchDdrRateByCurrentRate(
    VOS_UINT32                          ulDlRate,
    VOS_UINT32                          ulUlRate
)
{
#if defined(INSTANCE_1) || defined(INSTANCE_2)

#else
    TAF_APS_SWITCH_DDR_RATE_INFO_STRU  *pstSwitchDdrInfo;
    VOS_UINT32                          ulReqValue;
    VOS_UINT32                          ulMinDdrFlg;

    ulReqValue       = TAF_APS_GET_DSFLOW_MIN_DDR_BAND();
    pstSwitchDdrInfo = TAF_APS_GetSwitchDdrRateInfoAddr();
    ulMinDdrFlg      = VOS_FALSE;

    /* ��������ù����Ƶ���Ȿ�εĵ�Ƶ���ٴ��� */
    if (VOS_TRUE == pstSwitchDdrInfo->ulSetMaxFlag)
    {
        pstSwitchDdrInfo->ulSetMaxFlag = VOS_FALSE;
        return;
    }

    /* Ŀǰ��DDR��Ƶ����:
       ���д���72M,                                 DDR����533Mhz;
       ����С��72M����36M, �������д���36M,         DDR����360Mhz;
       ����С��36M����2M,  ��������С��36M����2M,   DDR����266Mhz;
       ����С��2M����300K, ��������С��2M����300K,  DDR����150Mhz;
       �����ж�С��300K,                            DDR����75Mhz.
    */

    /* ���ݵ�ǰ�����������ʲ���DDRͶƱ����ֵ */
    if (VOS_TRUE == TAF_APS_GET_MULTI_DFS_SUPPORT_FLG())
    {
        if (VOS_OK != TAF_APS_FindDfsReqValueByRat(&ulReqValue, ulDlRate, ulUlRate))
        {
            return;
        }
    }

    if (VOS_FALSE == TAF_APS_GET_MULTI_DFS_SUPPORT_FLG())
    {
        if (VOS_OK != TAF_APS_FindDfsReqValue(&ulReqValue, ulDlRate, ulUlRate))
        {
            return;
        }
    }


    /* ��ֹ�ظ�ͶƱ */
    if (ulReqValue == pstSwitchDdrInfo->ulReqValue)
    {
        return;
    }

    if (MDRV_OK != mdrv_pm_dfs_qos_update(DFS_QOS_ID_DDR_MINFREQ_E,
                                          pstSwitchDdrInfo->iDfsReqId,
                                          ulReqValue))
    {
        TAF_APS_DFS_UPDATE_FAIL_CNT(1);
        TAF_APS_SndOmDfsInfo(pstSwitchDdrInfo);
        return;
    }

    pstSwitchDdrInfo->ulReqValue = ulReqValue;
    TAF_APS_DFS_UPDATE_SUCC_CNT(1);

    TAF_APS_SndOmDfsInfo(pstSwitchDdrInfo);

    ulMinDdrFlg = TAF_APS_CheckIfMinDdrBand(ulReqValue);

    /* Ŀǰ����ͳ�Ƶ�ʱ����1�룬��ͻȻû������ʱ������̬�������뵽IDLE̬��CCPU
       ����˯�ߺ�����ͳ�ƶ�ʱ�����ٳ�ʱʱ��DDR֮ǰͶƱ����Ƶ����޷�������Ƶ��
       �����Ӷ�CCPU˯�ߵ�ͶƱ */
    /* ����С��300Kʱ�ͷ�CCPU˯��ͶƱ������300Kʱ��ֹCCPU˯�� */
    if (VOS_TRUE == ulMinDdrFlg)
    {
        (VOS_VOID)mdrv_pm_wake_unlock(PWRCTRL_SLEEP_DSFLOW);
    }
    else
    {
        (VOS_VOID)mdrv_pm_wake_lock(PWRCTRL_SLEEP_DSFLOW);
    }

#endif

    return;

}


/*****************************************************************************
 �� �� ��  : TAF_APS_SetDfsMax
 ��������  : ��DFS�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��17��
    ��    ��   : ���� 00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_APS_SetDfsMax(VOS_VOID)
{
    TAF_APS_SWITCH_DDR_RATE_INFO_STRU  *pstSwitchDdrInfo;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;

    pstSwitchDdrInfo = TAF_APS_GetSwitchDdrRateInfoAddr();

    /* ��Ƶ���ܲ�֧�֣���ʲô�������� */
    if (0 == TAF_APS_GET_DFS_PROFILE_NUM())
    {
        return;
    }
    /* ��ǰ������ʱ��û��������ʲô�������� */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_DSFLOW_REPORT,
                                           TAF_APS_INVALID_PDPID);
    if (TAF_APS_TIMER_STATUS_RUNING != enTimerStatus)
    {
        return;
    }

    /* �Ѿ�����ߵ�λ�����ٵ��� */
    if (TAF_APS_GET_DSFLOW_MAX_DDR_BAND() == pstSwitchDdrInfo->ulReqValue)
    {
        return;
    }

    /* ֱ�ӽ�DDR�������һ�� */
    if (MDRV_OK != mdrv_pm_dfs_qos_update(DFS_QOS_ID_DDR_MINFREQ_E,
                                          pstSwitchDdrInfo->iDfsReqId,
                                          TAF_APS_GET_DSFLOW_MAX_DDR_BAND()))

    {
        TAF_APS_DFS_UPDATE_FAIL_CNT(1);
        TAF_APS_SndOmDfsInfo(pstSwitchDdrInfo);
        return;
    }

    pstSwitchDdrInfo->ulReqValue   = TAF_APS_GET_DSFLOW_MAX_DDR_BAND();
    pstSwitchDdrInfo->ulSetMaxFlag = VOS_TRUE;
    TAF_APS_DFS_UPDATE_SUCC_CNT(1);
    (VOS_VOID)mdrv_pm_wake_lock(PWRCTRL_SLEEP_DSFLOW);
    TAF_APS_SndOmDfsInfo(pstSwitchDdrInfo);

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_CheckIfMinDdrBand
 ��������  : ȷ�ϵ�ǰ��ddrƵ���Ƿ�Ϊ��ǰ�Ľ��뼼����ӦddrƵ�ʵ���Сֵ
 �������  : VOS_UINT32 ulReqValue
 �������  : ��
 �� �� ֵ  : VOS_TRUE��VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��18��
    ��    ��   : ������ m00217266
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_CheckIfMinDdrBand(
    VOS_UINT32                          ulReqValue
)
{
    VOS_UINT32                          ulMinDdrBand;
    TAF_APS_DFS_TYPE_ENUM_UINT32        enDfsType;

    enDfsType    = TAF_APS_GetCurrDfsMode();

    if (0 == TAF_APS_GET_MULTI_DFS_PROFILE_NUM(enDfsType))
    {
        ulMinDdrBand = TAF_APS_GET_DSFLOW_MIN_DDR_BAND();
    }
    else
    {
        ulMinDdrBand = TAF_APS_GET_MULTI_DFS_PROFILE_DDR_BAND(enDfsType, 0);
    }

    if (ulMinDdrBand == ulReqValue)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_APS_ProcRlpDataStatus
 ��������  : APS�ṩ��RLP�Ļص�������RLPÿ20�������һ��
 �������  : pstRlpDataStat : RLP����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��27��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_ProcRlpDataStatusCb(
    const RLPITF_1X_RLP_DATA_STAT_STRU *const pstRlpDataStat
)
{
    VOS_UINT32                          i;
    static VOS_UINT32                   aulNoDataTimes[CTTF_1X_RLP_MAX_SRV_CONN_REC_NUM] = {0};
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           uc1xPktDataInactivityTimerLen;
    VOS_UINT8                           ucPreSetPktDataInactTimerLenInNv;

    ucPreSetPktDataInactTimerLenInNv = 5;

    if (0 == pstRlpDataStat->ucActiveConnsCnt)
    {
        return;
    }

    for (i = 0; i < TAF_APS_MIN(pstRlpDataStat->ucActiveConnsCnt, CTTF_1X_RLP_MAX_SRV_CONN_REC_NUM); i++)
    {
        /* ����Ҳ�����Ч��PDP ID��˵������Ч��Con_Ref����ֱ������ */
        ucPdpId = TAF_APS_GetPdpIdByConRef(pstRlpDataStat->astRlpBoValidFrame[i].ucConnReference);

        if (TAF_APS_INVALID_PDPID == ucPdpId)
        {
            continue;
        }

        /* TODO:������Ҫ�жϵ�ǰ�Ƿ���1Xģʽ�� */
        /* ���ucPdpId��Ӧ��״̬������TAF_APS_STA_ACTIVE����ս���dormant�ļ���  */
        if (TAF_APS_STA_ACTIVE != TAF_APS_GetPdpIdMainFsmState(ucPdpId))
        {
            aulNoDataTimes[i] = 0;
            TAF_INFO_LOG1(WUEPS_PID_TAF, "TAF_APS_ProcRlpDataStatusCb: clear 1x aulNoDataTimes of CTTF_1X_RLP_SRV_CONN_REC", i);
            continue;
        }

        if (PS_TRUE == pstRlpDataStat->astRlpBoValidFrame[i].enNonIdleNonFillFrameSentOrRcvd)
        {
            if (VOS_FALSE == TAF_APS_GetHysActivationInd())
            {
                TAF_APS_SetHysActivationInd(VOS_TRUE);

                TAF_APS_SndHaiChangeInd(ucPdpId);
            }
        }


        /* The mobile station shall maintain a packet data inactivity timer.  The value of this timer
             shall not be less than 5 seconds.  The timer should be reset whenever a RLP
             data frame is sent or received.  If the packet data inactivity timer expires, the mobile
             station should disconnect the packet data service option.  */
        uc1xPktDataInactivityTimerLen = TAF_APS_GetPktCdataInactivityTimerLen();

        if ((PS_TRUE == pstRlpDataStat->astRlpBoValidFrame[i].enNonIdleNonFillFrameSentOrRcvd)
          ||(0 == uc1xPktDataInactivityTimerLen))

        {
            aulNoDataTimes[i] = 0;

            if (ucPreSetPktDataInactTimerLenInNv != uc1xPktDataInactivityTimerLen)
            {
                TAF_INFO_LOG2(WUEPS_PID_TAF,
                             "TAF_APS_GetPktCdataInactivityTimerLen and aulNoDataTimes ",
                             uc1xPktDataInactivityTimerLen,
                             aulNoDataTimes[i]);
            }
        }
        else
        {
            aulNoDataTimes[i]++;

            if (aulNoDataTimes[i] > (VOS_UINT32)((uc1xPktDataInactivityTimerLen * 1000) / TAF_APS_CDATA_NO_DATA_TIME_LEN_PER_TIMES))
            {
                TAF_APS_SndEnterDormantInd(ucPdpId);
                aulNoDataTimes[i] = 0;
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ProcEvdoRlpDataStatusCb
 ��������  : APS�ṩ��RLP�Ļص�������RLPÿ80�������һ��
 �������  : enFlowActivity : RLP����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��02��
   ��    ��   : y00314741
   �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID TAF_APS_ProcEvdoRlpDataStatusCb(
    PS_BOOL_ENUM_UINT8                  enFlowActivity
)
{
    VOS_UINT8                           ucPdpId;
    static VOS_UINT32                   ulNoDataTime = 0;
    VOS_UINT8                           ucDoPktDataInactivityTimerLen;
    VOS_UINT8                           ucPreSetPktDataInactTimerLenInNv;

    ucPreSetPktDataInactTimerLenInNv = 5;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        /* ���ucPdpId��Ӧ��״̬������TAF_APS_STA_ACTIVE����ս���dormant�ļ��� */
        if (TAF_APS_STA_ACTIVE != TAF_APS_GetPdpIdMainFsmState(ucPdpId))
        {
            ulNoDataTime = 0;
            TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_APS_ProcEvdoRlpDataStatusCb: clear DO ulNoDataTime");
            continue;
        }

        if (TAF_APS_RAT_TYPE_LTE == TAF_APS_GetCurrPdpEntityDataServiceMode())
        {
            ulNoDataTime = 0;

            return;
        }

        if (TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
        {
            if (TAF_PS_CDATA_BEAR_STATUS_ACTIVE != TAF_APS_GetCdataEhrpdSvcSta(ucPdpId))
            {
                ulNoDataTime = 0;

                return;
            }
        }

        ucDoPktDataInactivityTimerLen = TAF_APS_GetPktCdataInactivityTimerLen();

        if ((PS_TRUE == enFlowActivity)
          ||(0 == ucDoPktDataInactivityTimerLen))
        {
            ulNoDataTime = 0;

            if (ucPreSetPktDataInactTimerLenInNv != ucDoPktDataInactivityTimerLen)
            {
                TAF_INFO_LOG2(WUEPS_PID_TAF,
                             "TAF_APS_GetPktCdataInactivityTimerLen and ulNoDataTime ",
                              ucDoPktDataInactivityTimerLen,
                              ulNoDataTime);
            }
        }
        else
        {
            ulNoDataTime++;

            if (ulNoDataTime > (VOS_UINT32)((ucDoPktDataInactivityTimerLen * 1000) / TAF_APS_CDATA_EVDO_NO_DATA_TIME_LEN_PER_TIMES))
            {
                TAF_APS_SndEnterDormantInd(ucPdpId);


                ulNoDataTime = 0;

                break;
            }

        }
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
