/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaFsmMain.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2013��7��9��
  ����޸�   :
  ��������   : ��״̬��������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��9��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "TafSdcCtx.h"
#include "MmaAppLocal.h"
#include "TafMmaCtx.h"
#include "Taf_Status.h"
#include "TafMmaSndInternalMsg.h"
#include "TafMmaMain.h"
#include "TafMmaSndApp.h"
#include "TafMmaComFunc.h"


/* Added by w00167002 for L-C��������Ŀ, 2014-2-20, begin */
#include "TafMmaMntn.h"
/* Added by w00167002 for L-C��������Ŀ, 2014-2-20, end */
#include "NasComm.h"
#include "TafMmaFsmMain.h"
#include "TafMmaFsmMainTbl.h"

#include "TafMmaSndMscc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define     THIS_FILE_ID        PS_FILE_ID_TAF_MMA_FSM_MAIN_C
#define     STA_WARNING_PRINT   PS_LOG_LEVEL_WARNING

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/
extern STATUS_CONTEXT_STRU                     g_StatusContext;
extern MMA_ME_PERSONALISATION_STATUS_STRU      g_stMmaMePersonalisationStatus;

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/

/*****************************************************************************
  6 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvAppPhoneModeSetReq_Main
 ��������  : �յ�OM��AT��ģʽ���úͲ�ѯ��Ϣ��������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAppPhoneModeSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PH_OP_MODE_STRU                *pstPhModeSet    = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstRcvMsg       = VOS_NULL_PTR;

    pstRcvMsg           = (MN_APP_REQ_MSG_STRU*)pstMsg;
    pstPhModeSet        = (TAF_PH_OP_MODE_STRU *)pstRcvMsg->aucContent;

    /* �ػ�ʱ��Ҫ�ж��Ƿ���Ҫ��ֹ��������,����ʱ����Ҫ�ж� */
    if ((STA_FSM_ENABLE   != g_StatusContext.ulFsmState)
     && (TAF_PH_MODE_FULL != pstPhModeSet->PhMode))
    {
        TAF_MMA_ProcPhoneStop_NotEnableStatus();
    }

    /* ����phone mode״̬�� */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}

/* Added by w00167002 for L-C��������Ŀ, 2014-2-14, begin */

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTafPhoneModeSetReq_Main
 ��������  : �յ�TAF��ģʽ������Ϣ��������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��02��14��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafPhoneModeSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PHONE_MODE_SET_REQ_STRU    *pstPhoneModeSetReq  = VOS_NULL_PTR;

    pstPhoneModeSetReq  = (TAF_MMA_PHONE_MODE_SET_REQ_STRU *)pstMsg;

    /* �ػ�ʱ��Ҫ�ж��Ƿ���Ҫ��ֹ��������,����ʱ����Ҫ�ж� */
    if ((STA_FSM_ENABLE   != g_StatusContext.ulFsmState)
     && (TAF_PH_MODE_FULL != pstPhoneModeSetReq->stPhoneModePara.PhMode))
    {
        TAF_MMA_ProcPhoneStop_NotEnableStatus();
    }

    /* ����phone mode״̬�� */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}

/* Added by w00167002 for L-C��������Ŀ, 2014-2-14, end */

/* Added by w00167002 for L-C��������Ŀ, 2014-2-14, begin */

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvSysCfgSetReq_Main
 ��������  : �յ�OM��AT��ģʽ���úͲ�ѯ��Ϣ��������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��02��14��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��02��14��
    ��    ��   : w00167002
    �޸�����   : DTS2014060305973:��PHONE MODE״̬��ʱ���û�����SYSCFG���ã���
                ���л��棬�ڴ�����ʱ��������º����޷��·�SYSCFG���á�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvSysCfgSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_SYS_CFG_REQ_STRU           *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (TAF_MMA_SYS_CFG_REQ_STRU *)pstMsg;

    switch (g_StatusContext.ulFsmState)
    {
        case STA_FSM_NULL:
        case STA_FSM_STOP:
            TAF_MMA_SetSyscfg_PowerOffStatus(pstRcvMsg);
            break;

        case STA_FSM_PLMN_RESEL:
            /* �����6F15�������Զ��������·�SYSCFG��
                  �����AT�����ģ���AT��֤���д����˴����账�� */
            if (TAF_MMA_AUTO_PLMN_SEL_USER_USIM_REFRESH == TAF_MMA_GetAutoPlmnSelUser())
            {
                /* ��״̬��֮ǰ��Ǩ�Ƶ�ǰL1״̬��SYSCFG״̬ */
                TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

                /* ����SYS CFG״̬�� */
                TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);
            }
            else
            {
                TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvSysCfgSetReq_Main: wrong state!");
            }

            break;

        case STA_FSM_ENABLE:
            /* ��״̬��֮ǰ��Ǩ�Ƶ�ǰL1״̬��SYSCFG״̬ */
            TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

            /* ����SYS CFG״̬�� */
            TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);
            break;


        default:
            TAF_MMA_SndSysCfgSetCnf(&(pstRcvMsg->stCtrl), TAF_ERR_CMD_TYPE_ERROR);

            break;
    }

    return VOS_TRUE;
}


/* Added by w00167002 for L-C��������Ŀ, 2014-2-14, end */

#if (FEATURE_ON == FEATURE_CSG)

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTafCsgListSearchReq_Main
 ��������  : �յ�OM��AT��ģʽCSG�б��ѵ�������
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��6��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafCsgListSearchReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CSG_LIST_SEARCH_REQ_STRU   *pstRcvMsg          = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx      = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_CTRL_STRU        *pstPlmnListCtrl    = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;
    VOS_UINT32                          ulRet;

    pstRcvMsg = (TAF_MMA_CSG_LIST_SEARCH_REQ_STRU *)pstMsg;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();


    /* ���g_stTafMmaCtx.astMmaOperCtx��TAF_MMA_OPER_CSG_LIST_SEARCH_REQ���ͽṹ���ڱ�ʹ�� */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_CSG_LIST_SEARCH_REQ))
    {
        /* ֱ�ӻظ�csg listʧ�� */
        TAF_MMA_ReportCsgListError(&(pstRcvMsg->stCtrl), TAF_ERR_TI_ALLOC_FAIL);

        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        /* ֱ�ӻظ�csg listʧ�� */
        TAF_MMA_ReportCsgListError(&(pstRcvMsg->stCtrl), TAF_ERR_TI_ALLOC_FAIL);

        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstRcvMsg->stCtrl,
                       TAF_MMA_OPER_CSG_LIST_SEARCH_REQ, ucCtxIndex);

    pstPlmnListCtrl = (TAF_MMA_PLMN_LIST_CTRL_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_PLMN_LIST_CTRL_STRU));
    if (NULL == pstPlmnListCtrl)
    {
        TAF_MMA_ReportCsgListError(&(pstRcvMsg->stCtrl), TAF_ERR_ERROR);

        return VOS_TRUE;
    }

    pstPlmnListCtrl->usCurrIndex = pstRcvMsg->stPlmnListPara.usCurrIndex;
    pstPlmnListCtrl->usReadNum   = pstRcvMsg->stPlmnListPara.usQryNum;

    pstMmaOperCtx[ucCtxIndex].pPara = (VOS_VOID *)pstPlmnListCtrl;

    /* ��mscc����csg list�������� */
    ulRet = TAF_MMA_SndMsccCsgListSearchReq();

    if ( VOS_ERR == ulRet )
    {
        TAF_MMA_ReportCsgListError(&(pstRcvMsg->stCtrl), TAF_ERR_ERROR);

        return VOS_TRUE;
    }

    /* ����CSG LIST״̬��־�� */
    g_StatusContext.ulFsmState               = STA_FSM_PLMN_LIST;

    /* ����CSG LIST״̬��ʱ�� */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_SEARCH_CNF, TI_TAF_MMA_WAIT_MSCC_CSG_LIST_SEARCH_CNF_LEN);

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccCsgListSearchCnf_Main
 ��������  : �յ�mscc��csg list�����ظ���Ϣ�Ĵ���
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��8��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccCsgListSearchCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_CSG_LIST_SEARCH_CFN_STRU  *pstCsgListSearchCnf = VOS_NULL_PTR;
    TAF_MMA_CSG_LIST_CTX_STRU          *pstCsgListCtx       = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx     = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;
    TAF_MMA_TIMER_STATUS_ENUM_UINT8     enWaitCsgListAbortCnfTimerStatus;
    VOS_UINT8                           ucCtxIndex;
    TAF_MMA_PLMN_LIST_CTRL_STRU        *pstPlmnListCtrl = VOS_NULL_PTR;

    pstCsgListCtx       = TAF_MMA_GetCsgListCtxAddr();
    pstCsgListSearchCnf = (MSCC_MMA_CSG_LIST_SEARCH_CFN_STRU *)pstMsg;
    pstCsgListCtx       = TAF_MMA_GetCsgListCtxAddr();
    pstMmaOperCtx       = TAF_MMA_GetOperCtxAddr();

    if ( STA_FSM_PLMN_LIST != g_StatusContext.ulFsmState)
    {
        return VOS_TRUE;
    }

    /* ֹͣ��csg list�����ظ���ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_SEARCH_CNF);

    /* at csg abort������csg list�����ظ��Գ峡������Ҫ�ظ�abort cnf */
    enWaitCsgListAbortCnfTimerStatus = TAF_MMA_GetTimerStatus(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF);

    if ((TAF_MMA_PLMN_LIST_ABORT_PROCESSING_USER_ABORT == TAF_MMA_GetCsgListAbortType())
     && (TAF_MMA_TIMER_STATUS_RUNING == enWaitCsgListAbortCnfTimerStatus))
    {
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF);

        if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CSG_LIST_ABORT_REQ, &ucCtxIndex))
        {
            /*  �ظ�LIST_ABORT_CNF */
            TAF_MMA_SndCsgListAbortCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), TAF_ERR_NO_ERROR);

            TAF_MMA_ClearOperCtx(ucCtxIndex);
            TAF_MMA_ClearCsgListSearchOperCtx();

            /* Ǩ��״̬��ENABLE״̬ */
            g_StatusContext.ulFsmState = STA_FSM_ENABLE;

            /* ���õ�ǰû�д����û�CSG�б��Ѵ�Ϲ��� */
            TAF_MMA_SetCsgListAbortType(TAF_MMA_PLMN_LIST_ABORT_BUTT);
            return VOS_TRUE;
        }
    }

    pstCsgListCtx->ulPlmnWithCsgIdNum = (VOS_UINT8)TAF_SDC_MIN(TAF_SDC_MAX_CSG_ID_LIST_NUM, pstCsgListSearchCnf->stCsgIdInfo.ulPlmnWithCsgIdNum);


    /* ���������������ȫ�ֱ����� */
    for (ulIndex = 0; ulIndex < pstCsgListCtx->ulPlmnWithCsgIdNum; ulIndex++)
    {
        pstCsgListCtx->astCsgIdListInfo[ulIndex].stPlmnId.Mcc           = pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].stPlmnId.ulMcc;
        pstCsgListCtx->astCsgIdListInfo[ulIndex].stPlmnId.Mnc           = pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].stPlmnId.ulMnc;
        pstCsgListCtx->astCsgIdListInfo[ulIndex].enPlmnWithCsgIdType    = pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].enPlmnWithCsgIdType;
        pstCsgListCtx->astCsgIdListInfo[ulIndex].ulCsgId                = pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].ulCsgId;
        pstCsgListCtx->astCsgIdListInfo[ulIndex].ucRaMode               = pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].enRatType;

        pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgType.ucCsgTypeLen = TAF_SDC_MIN(TAF_MMA_MAX_CSG_TYPE_LEN,pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].ucCsgTypeLen);
        PS_MEM_CPY(pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgType.aucCsgType,
                   pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].aucCsgType,
                   sizeof(pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgType.aucCsgType));

        pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgIdHomeNodeBName.ucHomeNodeBNameLen = TAF_SDC_MIN(TAF_MMA_MAX_HOME_NODEB_NAME_LEN, pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].ucHomeNodeBNameLen);
        PS_MEM_CPY(pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgIdHomeNodeBName.aucHomeNodeBName,
                   pstCsgListSearchCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].aucHomeNodeBName,
                   sizeof(pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgIdHomeNodeBName.aucHomeNodeBName));
    }

    /* �ϱ���� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CSG_LIST_SEARCH_REQ, &ucCtxIndex))
    {
        pstPlmnListCtrl = (TAF_MMA_PLMN_LIST_CTRL_STRU *)pstMmaOperCtx[ucCtxIndex].pPara;
        TAF_MMA_ReportCsgListSearchResult(&(pstMmaOperCtx[ucCtxIndex].stCtrl), pstPlmnListCtrl);
    }

    /* ״̬�ָ� */
    g_StatusContext.ulFsmState = STA_FSM_ENABLE;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccCsgListRej_Main
 ��������  : �յ�mscc��csg list rej��Ϣ�Ĵ���
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��12��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccCsgListRej_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstMmaOperCtx      = TAF_MMA_GetOperCtxAddr();

    /* ����CSG LIST״̬ */
    if ( STA_FSM_PLMN_LIST != g_StatusContext.ulFsmState )
    {
        /* ������ٵ�����Ϣ */
        STA_TRACE (STA_WARNING_PRINT,
            "TAF_MMA_RcvMsccCsgListRej_Main():WARNING:unmatched system FSM state\n" );

        return VOS_TRUE;
    }

    /* ֹͣ״̬��ʱ��*/
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_SEARCH_CNF);

    /* �����״̬ */
    g_StatusContext.ulFsmState = STA_FSM_ENABLE;

    if (VOS_FALSE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CSG_LIST_SEARCH_REQ, &ucCtxIndex))
    {
        STA_TRACE(PS_LOG_LEVEL_ERROR,"TAF_MMA_RcvMsccCsgListRej_Main:ERROR: GET CTX FAIL.");
        return VOS_TRUE;
    }

    TAF_MMA_ReportCsgListError(&(pstMmaOperCtx[ucCtxIndex].stCtrl), TAF_ERR_CMD_TYPE_ERROR);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMsccCsgListAbortCnf_Main
 ��������  : �յ�mscc��csg list abort�ظ���Ϣ�Ĵ���
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��8��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMsccCsgListAbortCnf_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_CSG_LIST_ABORT_CNF_STRU   *pPlmnListAbortCnf = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx     = VOS_NULL_PTR;
    TAF_MMA_CSG_LIST_CTX_STRU          *pstCsgListCtx     = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_CTRL_STRU        *pstPlmnListCtrl   = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucCtxIndex;

    pstCsgListCtx     = TAF_MMA_GetCsgListCtxAddr();
    pPlmnListAbortCnf = (MSCC_MMA_CSG_LIST_ABORT_CNF_STRU*)pstMsg;
    pstMmaOperCtx     = TAF_MMA_GetOperCtxAddr();

    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF);

    /* ��ǰ����CSG LIST״̬��ֱ�ӷ��� */
    if (STA_FSM_PLMN_LIST != g_StatusContext.ulFsmState)
    {
        STA_TRACE(STA_WARNING_PRINT, "TAF_MMA_RcvMsccCsgListAbortCnf_Main():WARNING:Sta_UpdateFsmFlag failed\n");
        return VOS_TRUE;
    }

    /* �쳣��������ǰû�����ڴ���CSG�б��Ѵ�ϣ�ֱ�ӷ��� */
    if (TAF_MMA_PLMN_LIST_ABORT_BUTT == TAF_MMA_GetCsgListAbortType())
    {
        STA_TRACE(STA_WARNING_PRINT, "TAF_MMA_RcvMsccCsgListAbortCnf_Main():WARNING:Sta_UpdateFsmFlag failed\n");
        return VOS_TRUE;
    }

    /* ��ʱ����ʱ���µ� LIST ABORT�Ĵ��� */
    if ( TAF_MMA_PLMN_LIST_ABORT_PROCESSING_TIMEOUT == TAF_MMA_GetCsgListAbortType())
    {
        /* stop cnf��search cnf�Գ�ʱ�п��ܴ��������б�Ϊ�գ���Ҫ�ϱ�, ���������������ȫ�ֱ����� */
        if (pPlmnListAbortCnf->stCsgIdInfo.ulPlmnWithCsgIdNum > 0)
        {
            for (ulIndex = 0; ulIndex < TAF_SDC_MIN(TAF_SDC_MAX_CSG_ID_LIST_NUM, pPlmnListAbortCnf->stCsgIdInfo.ulPlmnWithCsgIdNum); ulIndex++)
            {
                pstCsgListCtx->astCsgIdListInfo[ulIndex].stPlmnId.Mcc           = pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].stPlmnId.ulMcc;
                pstCsgListCtx->astCsgIdListInfo[ulIndex].stPlmnId.Mnc           = pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].stPlmnId.ulMnc;
                pstCsgListCtx->astCsgIdListInfo[ulIndex].enPlmnWithCsgIdType    = pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].enPlmnWithCsgIdType;
                pstCsgListCtx->astCsgIdListInfo[ulIndex].ulCsgId                = pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].ulCsgId;
                pstCsgListCtx->astCsgIdListInfo[ulIndex].ucRaMode               = pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].enRatType;

                pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgType.ucCsgTypeLen = TAF_SDC_MIN(TAF_MMA_MAX_CSG_TYPE_LEN,pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].ucCsgTypeLen);
                PS_MEM_CPY(pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgType.aucCsgType,
                    pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].aucCsgType,
                    sizeof(pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgType.aucCsgType));

                pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgIdHomeNodeBName.ucHomeNodeBNameLen = TAF_SDC_MIN(TAF_MMA_MAX_HOME_NODEB_NAME_LEN, pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].ucHomeNodeBNameLen);
                PS_MEM_CPY(pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgIdHomeNodeBName.aucHomeNodeBName,
                    pPlmnListAbortCnf->stCsgIdInfo.astPlmnWithCsgIdList[ulIndex].aucHomeNodeBName,
                    sizeof(pstCsgListCtx->astCsgIdListInfo[ulIndex].stCsgIdHomeNodeBName.aucHomeNodeBName));
            }

            pstCsgListCtx->ulPlmnWithCsgIdNum = (VOS_UINT8)TAF_SDC_MIN(TAF_SDC_MAX_CSG_ID_LIST_NUM, pPlmnListAbortCnf->stCsgIdInfo.ulPlmnWithCsgIdNum);

            /* �ϱ���� */
            if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CSG_LIST_SEARCH_REQ, &ucCtxIndex))
            {
                pstPlmnListCtrl = (TAF_MMA_PLMN_LIST_CTRL_STRU *)pstMmaOperCtx[ucCtxIndex].pPara;
                TAF_MMA_ReportCsgListSearchResult(&(pstMmaOperCtx[ucCtxIndex].stCtrl), pstPlmnListCtrl);
            }

            /* ״̬�ָ� */
            g_StatusContext.ulFsmState = STA_FSM_ENABLE;

            /* ���õ�ǰû�д����û�CSG�б��Ѵ�Ϲ��� */
            TAF_MMA_SetCsgListAbortType(TAF_MMA_PLMN_LIST_ABORT_BUTT);
            return VOS_TRUE;
        }

        /* abort cnf�в�Я������,�ϱ����б� */
        if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CSG_LIST_SEARCH_REQ, &ucCtxIndex))
        {
            TAF_MMA_ReportCsgListError(&(pstMmaOperCtx[ucCtxIndex].stCtrl), TAF_ERR_TIME_OUT);
        }

        /* ״̬�ָ� */
        g_StatusContext.ulFsmState = STA_FSM_ENABLE;

        /* ���õ�ǰû�д����û�CSG�б��Ѵ�Ϲ��� */
        TAF_MMA_SetCsgListAbortType(TAF_MMA_PLMN_LIST_ABORT_BUTT);
        return VOS_TRUE;

    }

    /* AT�·���csg list abort����AT�ظ��б��ѳ�ʱ��� */
    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_CSG_LIST_ABORT_REQ, &ucCtxIndex))
    {
        /*  �ظ�LIST_ABORT_CNF */
        TAF_MMA_SndCsgListAbortCnf(&(pstMmaOperCtx[ucCtxIndex].stCtrl), TAF_ERR_NO_ERROR);

        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }

    TAF_MMA_ClearCsgListSearchOperCtx();

    /* Ǩ��״̬��ENABLE״̬ */
    g_StatusContext.ulFsmState = STA_FSM_ENABLE;

    /* ���õ�ǰû�д����û�CSG�б��Ѵ�Ϲ��� */
    TAF_MMA_SetCsgListAbortType(TAF_MMA_PLMN_LIST_ABORT_BUTT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTafCsgListAbortReq_Main
 ��������  : �յ�OM��AT��ģʽCSG�б��Ѵ����Ϣ��������
 �������  : ulEventType - �¼�����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��6��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafCsgListAbortReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_CSG_LIST_ABORT_REQ_STRU    *pstPlmnListAbortMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucCtxIndex;

    pstPlmnListAbortMsg = (TAF_MMA_CSG_LIST_ABORT_REQ_STRU *)pstMsg;

    /* MMA�ϱ�CSG LIST CNF���б��Ѵ�϶Գ�ʱ����ǰ״̬�Ѳ���CSG LIST״̬��
       ֱ�Ӹ�AT�ظ�abort cnf */
    if ( STA_FSM_PLMN_LIST != g_StatusContext.ulFsmState )
    {
        /* �ϱ�AT��ǰ״̬�¼� */
        TAF_MMA_SndCsgListAbortCnf(&pstPlmnListAbortMsg->stCtrl, TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    /* ��ʱ����ʱ���CSG�б��Ѻ��û����CSG�б��ѶԳ�ʱ�����û����Ϊ׼ */
    if (TAF_MMA_PLMN_LIST_ABORT_PROCESSING_TIMEOUT == TAF_MMA_GetCsgListAbortType())
    {
        /* ���õ�ǰ���ڴ����û�CSG����б��ѹ��� */
        TAF_MMA_SetCsgListAbortType(TAF_MMA_PLMN_LIST_ABORT_PROCESSING_USER_ABORT);

        return VOS_TRUE;
    }

    /* ͣCSG�б��Ѷ�ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_SEARCH_CNF);

    /* ���g_stTafMmaCtx.astMmaOperCtx��TAF_MMA_OPER_CSG_LIST_ABORT_REQ���ͽṹ���ڱ�ʹ�� */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_CSG_LIST_ABORT_REQ))
    {
        /* ֱ�ӻظ�LIST ABORT����ʧ�� */
        TAF_MMA_SndCsgListAbortCnf(&pstPlmnListAbortMsg->stCtrl, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndCsgListAbortCnf(&pstPlmnListAbortMsg->stCtrl, TAF_ERR_NO_ERROR);
        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstPlmnListAbortMsg->stCtrl,
                       TAF_MMA_OPER_CSG_LIST_ABORT_REQ, ucCtxIndex);

    /* MMA��LIST����������ʱ����ʱ��������MSCC����ֹͣLIST��������
       �յ�MSCC�Ļظ�������AT�ظ� */
    ulRet = TAF_MMA_SndMsccCsgListAbortReq();

    if (VOS_ERR == ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvTafCsgListAbortReq_Main():ERROR: failed");
        return VOS_TRUE;
    }

    /* ����10s��ʱ���������ʱδ�յ�MSCC�Ļظ����ϱ�ATʧ�� */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF, TI_TAF_MMA_WAIT_MSCC_CSG_LIST_ABORT_CNF_LEN);

    /* ���õ�ǰ���ڽ����û����CSG�б��ѹ��� */
    TAF_MMA_SetCsgListAbortType(TAF_MMA_PLMN_LIST_ABORT_PROCESSING_USER_ABORT);

    return VOS_TRUE;
}


#endif

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaPlmnListReq_Main
 ��������  : �յ�OM��AT��ģʽ�б��ѵ�������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��12��
    ��    ��   : b00269685
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaPlmnListReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PLMN_LIST_REQ_STRU         *pstRcvMsg          = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx      = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_CTRL_STRU        *pstPlmnListCtrl    = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_CNF_PARA_STRU    *pstPlmnListCnfPara = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstRcvMsg = (TAF_MMA_PLMN_LIST_REQ_STRU *)pstMsg;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    pstPlmnListCnfPara = (TAF_MMA_PLMN_LIST_CNF_PARA_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));
    if (NULL == pstPlmnListCnfPara)
    {
        return VOS_TRUE;
    }

    PS_MEM_SET(pstPlmnListCnfPara, 0x0, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));

    /* ���g_stTafMmaCtx.astMmaOperCtx��TAF_MMA_OPER_PLMN_LIST_REQ���ͽṹ���ڱ�ʹ�� */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_PLMN_LIST_REQ))
    {
        /* ֱ�ӻظ�plmn listʧ�� */
        pstPlmnListCnfPara->ucOpError    = VOS_TRUE;
        pstPlmnListCnfPara->enPhoneError = TAF_ERR_TI_ALLOC_FAIL;
        TAF_MMA_SndPlmnListCnf(&(pstRcvMsg->stCtrl), pstPlmnListCnfPara);

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
         /* ֱ�ӻظ�plmn listʧ�� */
        pstPlmnListCnfPara->ucOpError    = VOS_TRUE;
        pstPlmnListCnfPara->enPhoneError = TAF_ERR_TI_ALLOC_FAIL;
        TAF_MMA_SndPlmnListCnf(&(pstRcvMsg->stCtrl), pstPlmnListCnfPara);

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstRcvMsg->stCtrl,
                       TAF_MMA_OPER_PLMN_LIST_REQ, ucCtxIndex);

    pstPlmnListCtrl = (TAF_MMA_PLMN_LIST_CTRL_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_PLMN_LIST_CTRL_STRU));
    if (NULL == pstPlmnListCtrl)
    {
        /* ֱ�ӻظ�plmn listʧ�� */
        TAF_MMA_PlmnListErrorReport(TAF_ERR_ERROR);

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    pstPlmnListCtrl->usCurrIndex = pstRcvMsg->stPlmnListPara.usCurrIndex;
    pstPlmnListCtrl->usReadNum   = pstRcvMsg->stPlmnListPara.usQryNum;

    pstMmaOperCtx[ucCtxIndex].pPara = (VOS_VOID *)pstPlmnListCtrl;

    /* ������Ƿֶ��ϱ��е��״β�ѯ����ֱ�ӵ��û����е������ϱ� */
    if (0 != pstPlmnListCtrl->usCurrIndex)
    {
        Sta_PlmnListEventReport();

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

    /* ����ԭ�е�plmn list���� */
    MMA_PhonePlmnList();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaInterPowerInit_Main
 ��������  : �յ�MMA���ڲ��ϵ���Ϣ��������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaInterPowerInit_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����phone mode״̬�� */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaInterUsimStatusChangeInd_Main
 ��������  : �յ�MMA���ڲ���״̬�ı���Ϣ��������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��2��19��
    ��    ��   : w00167002
    �޸�����   : �������PIN��STK IMSI�ı䣬3G session������������¹ػ��Ϳ�����
                 ���У�USIMģ��ֱ��ϱ���״̬��Ϣ��MMA��CDMA modem����ʱ����CDMA
                 modem�ٴ���Balong modem�ػ���������, Balong modem���Զ����йػ�
                 �Ϳ�������������Balong modemû�п��������������ԣ���������ʼ����
                 CDMA modem���.
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaInterUsimStatusChangeInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (STA_FSM_ENABLE != g_StatusContext.ulFsmState)
    {
        TAF_MMA_ProcPhoneStop_NotEnableStatus();
    }

    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-19, begin */

    /* �����ǰΪCLģʽ����ȴ�CDMA�����ػ� */
    if (VOS_TRUE == TAF_SDC_IsConfigCLInterWorkCOutside())
    {
        return VOS_TRUE;
    }
    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-19, end */



    /* ����phone mode״̬�� */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaSimlockStatusChangeInd_Main
 ��������  : �յ�MMA����������״̬�ı���Ϣ��������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��12��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaSimlockStatusChangeInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (STA_FSM_ENABLE != g_StatusContext.ulFsmState)
    {
        TAF_MMA_ProcPhoneStop_NotEnableStatus();
    }

    /* ����phone mode״̬�� */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaPhoneModeRsltInd_Main
 ��������  : �յ�MMA��ģʽ����״̬���˳���Ϣ��������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��2��18��
    ��    ��   : w00167002
    �޸�����   : L-C��������Ŀ:�ڹػ�ʱ�򣬳�ʼ��CL����������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaPhoneModeRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-18, begin */
    TAF_MMA_PHONE_MODE_RSLT_IND_STRU   *pstPhoneModeRslt    = VOS_NULL_PTR;
    TAF_SDC_CTX_STRU                   *pstSdcCtx           = VOS_NULL_PTR;

    pstPhoneModeRslt = (TAF_MMA_PHONE_MODE_RSLT_IND_STRU*)pstMsg;
    pstSdcCtx = TAF_SDC_GetSdcCtx();
    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-18, end */

    if (TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_SUCC == pstPhoneModeRslt->enRslt)
    {
        /*����ʹ��״̬������״̬��־��*/
        g_StatusContext.ulFsmState = STA_FSM_ENABLE;
    }
    else
    {
        /* ��ʼ��ȫ�ֱ��� */
        TAF_MMA_InitCtx(TAF_MMA_INIT_CTX_POWEROFF, TAF_MMA_GetMmaCtxAddr());

        TAF_SDC_InitServiceInfo(&pstSdcCtx->stServiceInfo);

        /* Added by w00167002 for L-C��������Ŀ, 2014-2-18, begin */
        TAF_SDC_InitLcConfigPara(&(pstSdcCtx->stMsCfgInfo.stMsCapInfo.stLcConfigPara));
        /* Added by w00167002 for L-C��������Ŀ, 2014-2-18, end */

        g_StatusContext.ulFsmState = STA_FSM_NULL;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaSysCfgRsltInd_Main
 ��������  : �յ�MMA��SysCfg״̬���˳���Ϣ��������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��5��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaSysCfgRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucOrigLockStatus;

    TAF_MMA_SYS_CFG_RSLT_STRU          *pstSysCfgRslt   = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubMode;
    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncTafSdcSysmodServiceRegStaUpdate;

    pFuncTafSdcSysmodServiceRegStaUpdate = VOS_NULL_PTR;
    enSysMode = TAF_SDC_SYS_MODE_BUTT;
    enSubMode = TAF_SDC_SYS_SUBMODE_BUTT;

    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        if (VOS_FALSE == TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_LTE))
        {
            TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_LTE_NETWORK_NOT_EXIST, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_ChgSysModeAndSrvRegSta(TAF_PH_ACCESS_TECH_E_UTRAN,
                                           enSysMode,
                                           enSubMode,
                                           pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
        }

        if (VOS_FALSE == TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_CDMA_1X))
        {
            TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_1X_NETWORK_NOT_EXIST, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_ChgSysModeAndSrvRegSta(TAF_PH_ACCESS_TECH_CDMA_1X,
                                           enSysMode,
                                           enSubMode,
                                           pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
        }

        if (VOS_FALSE == TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_EVDO))
        {
            TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_HRPD_NETWORK_NOT_EXIST, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_ChgSysModeAndSrvRegSta(TAF_PH_ACCESS_TECH_EVDO,
                                           enSysMode,
                                           enSubMode,
                                           pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
        }
    }

    /* �ϱ���ǰ���Ƿ���CLģʽ */
    TAF_MMA_SndCLModeInd();
#endif

    pstSysCfgRslt   = (TAF_MMA_SYS_CFG_RSLT_STRU *)pstMsg;

    /* �˳�SYSCFG״̬����Ǩ�Ƶ�ǰL1״̬��idle״̬ */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_IDLE);

#ifdef DMT
    return VOS_TRUE;
#endif

    if (TAF_MMA_SYS_CFG_RSLT_SYS_CFG_SUCC != pstSysCfgRslt->enRslt)
    {
        return VOS_TRUE;
    }

    /* GUL->CL��CL->GULʱ��Ҫ�����ж���������״̬���������仯�跢��USIMM STATUS CHANGE��Ϣ */
    if (VOS_FALSE == pstSysCfgRslt->ucIsNeedChkLock)
    {
        return VOS_TRUE;
    }

    /* ��������״̬��� */
    ucOrigLockStatus = g_stMmaMePersonalisationStatus.SimLockStatus;

    g_stMmaMePersonalisationStatus.SimLockStatus = MMA_SIM_IS_UNLOCK;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* ����Ƿ����� */
        (VOS_VOID)MMA_CheckCsimMePersonalisationStatus();
    }
    else
#endif
    {
        /* ����Ƿ����� */
        (VOS_VOID)MMA_CheckMePersonalisationStatus();
    }

    /* ��������״̬������� */
    if (g_stMmaMePersonalisationStatus.SimLockStatus   != ucOrigLockStatus)
    {
        TAF_MMA_SndInterUsimChangeInd();
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaInterSysCfgSetReq_Main
 ��������  : �յ�MMA���ڲ�SYS CFG���������������
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaInterSysCfgSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��״̬��֮ǰ��Ǩ�Ƶ�ǰL1״̬��SYSCFG״̬ */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

    /* ����SYS CFG״̬�� */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvPihUsimStatusInd_Main
 ��������  : �յ�PBģ���ϱ��Ŀ�״ָ̬ʾ��Ϣ��������
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��10��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �����ڲ���״̬�ı���Ϣ */
    TAF_MMA_SndInterUsimChangeInd();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvUsimRefreshIndMsg_Main
 ��������  : �յ�usim���ļ�ˢ��ָʾ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��10��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvUsimRefreshIndMsg_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �����ڲ���״̬�ı���Ϣ */
    TAF_MMA_SndInterUsimChangeInd();

    return VOS_TRUE;
}

/* Added by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvDetachReq_Main
 ��������  : �յ�Detach��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��2��14��
   ��    ��   : s00246516
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��4��20��
   ��    ��   : h00313353
   �޸�����   : SysCfg Reconsitution
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvDetachReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_DETACH_REQ_STRU            *pstDetachReqMsg;

    pstDetachReqMsg                     = (TAF_MMA_DETACH_REQ_STRU *)pstMsg;

    /* ENABLE��RESTART״̬�������DETACH */
    if (VOS_TRUE != TAF_MMA_IsEnableDeAttach())
    {
        TAF_MMA_SndDetachCnf(&(pstDetachReqMsg->stCtrl),
                             TAF_MMA_APP_OPER_RESULT_FAILURE,
                             TAF_ERR_ERROR);

        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvDetachReq_Main():FSM state not in Enabled or Restart!");

        return VOS_TRUE;
    }

    /* ��״̬��֮ǰ��Ǩ�Ƶ�ǰL1״̬��SYSCFG״̬ */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

    /* ����System Config״̬�� */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);

    return VOS_TRUE;
}
/* Added by s00246516 for L-C��������Ŀ, 2014-02-14, End */



/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvAttachReq_Main
 ��������  :  ��״̬���յ�ID_TAF_MMA_ATTACH_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��11��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAttachReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ENABLE����refresh�������Զ�����������attach */
    if (VOS_TRUE != TAF_MMA_IsEnableDeAttach())
    {
        TAF_MMA_SndAttachCnf(&(((TAF_MMA_ATTACH_REQ_STRU *)pstMsg)->stCtrl),
                             TAF_MMA_APP_OPER_RESULT_FAILURE,
                             TAF_ERR_PHONE_MSG_UNMATCH);

        return VOS_TRUE;
    }
    /* ��״̬��֮ǰ��Ǩ�Ƶ�ǰL1״̬��SYSCFG״̬ */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

    /* ����SYS CFG״̬�� */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);

    return VOS_TRUE;
}


#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
 �� �� ��  : TAF_MMA_IsRefreshTrigger_PreProc
 ��������  : �Ƿ���refresh����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
             VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��03��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsRefreshTrigger_Main(VOS_VOID)
{
    TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8 enAutoPlmnSelUser;

    enAutoPlmnSelUser = TAF_MMA_GetAutoPlmnSelUser();

    /* refresh�������Զ����� */
    if ((STA_FSM_PLMN_RESEL == g_StatusContext.ulFsmState)
     && (TAF_MMA_AUTO_PLMN_SEL_USER_USIM_REFRESH == enAutoPlmnSelUser))
    {
        return VOS_TRUE;
    }

    /* refresh������SYSCFG*/
    /* �����SYSCFG���̣���SYSCFG״̬���д���abort���˴�ɾ�� */

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcImsSwitchOff_PreProc
 ��������  : IMS�رյ�Ԥ����
 �������  : pstImsSwitchSet
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��03��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_ProcImsSwitchOff_Main(
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU     *pstImsSwitchSet
)
{
    TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8 enLastState;
    VOS_UINT32                          ulPhoneMode;

    enLastState      = TAF_SDC_GetCurImsSwitchState();
    ulPhoneMode      = TAF_SDC_GetCurPhoneMode();

    /* �����ǰ����IMSҵ������У�������ر�IMSҵ�� */
    if (VOS_TRUE == TAF_SDC_IsImsSrvExist())
    {
        /* ���ϲ�ظ�ʧ�� */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_REJECT,
                                   TAF_ERR_IMS_SERVICE_EXIST);

        return VOS_TRUE;
    }

    /* ���������ѡ�����ó���PS_ONLY��������ر�IMSҵ�� */
    if (TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY == TAF_SDC_GetVoiceDomain())
    {
        /* ���ϲ�ظ�ʧ�� */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_REJECT,
                                   TAF_ERR_IMS_VOICE_DOMAIN_PS_ONLY);

        return VOS_TRUE;
    }

    /* ����IMSҵ������������NV */
    if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportFlag(VOS_FALSE))
    {
        /* ���ϲ�ظ�ʧ�� */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_FAILURE,
                                   TAF_ERR_UNSPECIFIED_ERROR);
        return VOS_TRUE;
    }

    /* ��ǰIMSЭ��ջ�Ѿ��رջ��ߴ��ڷ���ģʽ״̬��
       ����Ҫ��IMSA���ر�����ֻ����NV���� */
    if ((TAF_SDC_IMS_SWITCH_STATE_OFF == enLastState)
     || (TAF_PH_MODE_FULL != ulPhoneMode))
    {
        /* ���ϲ�ظ��ɹ� */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_SUCCESS,
                                   TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcImsSwitchOn_PreProc
 ��������  : IMS�򿪵�Ԥ����
 �������  : pstImsSwitchSet
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ϣ�������
             VOS_FALSE:��Ϣδ�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��03��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_ProcImsSwitchOn_Main(
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU     *pstImsSwitchSet
)
{
    TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8 enLastState;
    VOS_UINT32                          ulPhoneMode;

    enLastState      = TAF_SDC_GetCurImsSwitchState();
    ulPhoneMode      = TAF_SDC_GetCurPhoneMode();

    /* ����NV���ڸ�IMSA����start req��ǰ�棬IMSA�յ�start req���NV���Ҫ�����µ�NVֵ */
    if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportFlag(VOS_TRUE))
    {
        /* ���ϲ�ظ�ʧ�� */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_FAILURE,
                                   TAF_ERR_UNSPECIFIED_ERROR);

        return VOS_TRUE;
    }

    /* ��ǰIMSЭ��ջ�Ѿ��������ߴ��ڷ���ģʽ״̬��
       ����Ҫ��IMSA����������ֻ����NV����  */
    if ((TAF_SDC_IMS_SWITCH_STATE_ON == enLastState)
     || (TAF_PH_MODE_FULL != ulPhoneMode))
    {
        /* ���ϲ�ظ��ɹ� */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_SUCCESS,
                                   TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTafImsSwitchSetReq_Main
 ��������  : �յ�TAF��IMS������Ϣ��������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTafImsSwitchSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU    *pstSetReq   = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    ulResult   = VOS_TRUE;
    pstSetReq  = (TAF_MMA_IMS_SWITCH_SET_REQ_STRU *)pstMsg;


    /* �����ǰ������AT�������ڴ�����ֱ�Ӹ��ϲ�ظ�ʧ�ܣ�
       �������������������IMS���أ�������ظ���ʱ����Ҫ���� */
    if ((STA_FSM_ENABLE != g_StatusContext.ulFsmState)
     && (STA_FSM_NULL   != g_StatusContext.ulFsmState)
     && (STA_FSM_STOP   != g_StatusContext.ulFsmState))
    {
        /* ���ǿ������ģ�����AT���������� */
        if (VOS_FALSE == TAF_MMA_IsRefreshTrigger_Main())
        {
            /* ���ϲ�ظ�ʧ�� */
            TAF_MMA_SndImsSwitchSetCnf(&pstSetReq->stCtrl,
                                       TAF_MMA_APP_OPER_RESULT_FAILURE,
                                       TAF_ERR_UNSPECIFIED_ERROR);

            return VOS_TRUE;
        }
    }

    /* �ر�IMSҵ�� */
    if (TAF_MMA_IMS_SWITCH_SET_POWER_OFF == pstSetReq->enImsSwitch)
    {
        ulResult = TAF_MMA_ProcImsSwitchOff_Main(pstSetReq);
    }
    else
    {
        ulResult = TAF_MMA_ProcImsSwitchOn_Main(pstSetReq);
    }

    /* ����VOS_FALSE��������Ҫ������IMS_SWITCH״̬������ */
    if ( VOS_FALSE == ulResult )
    {
        /* ����IMS SWITCH״̬�� */
        TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_IMS_SWITCH);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvMmaImsSwitchRsltInd_Main
 ��������  : �յ�MMA��IMS SWITCH״̬���˳���Ϣ��������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-02-04
    ��    ��   : n00269697
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaImsSwitchRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ʱû�д���ֻ��Ϊ�˺����Ļ��洦���Ժ��������Ҫ��������������Ӵ��� */

    return VOS_TRUE;
}
#endif



/**********************************************************
 �� �� ��  : TAF_MMA_RcvPlmnSpecialSelReq_Main
 ��������  : �����û�ָ��������
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��3��25��
    ��    ��   : f00279542
    �޸�����   : CDMA Iteration 11 �ع��޸�
*************************************************************/
VOS_UINT32 TAF_MMA_RcvPlmnSpecialSelReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PLMN_ID_STRU                    stPlmn;
    VOS_UINT32                          ulRet;
    TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU  *pstPlmnSpecialSelMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstPlmnSpecialSelMsg = (TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU *)pstMsg;

    /* ���g_stTafMmaCtx.astMmaOperCtx��TAF_MMA_OPER_PLMN_SPEC_SEL_REQ���ͽṹ���ڱ�ʹ�� */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_PLMN_SPEC_SEL_REQ))
    {
        /* ֱ�ӻظ�SEL����ʧ�� */
        TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnSpecialSelMsg->stCtrl, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnSpecialSelMsg->stCtrl, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstPlmnSpecialSelMsg->stCtrl,
                       TAF_MMA_OPER_PLMN_SPEC_SEL_REQ, ucCtxIndex);

    /* ��CLģʽʱ�򣬲�֧��AT����ѡ������,ֱ�ӷ���ERROR */
    if (VOS_TRUE == TAF_MMA_IsPowerOnCLInterWork())
    {
        TAF_MMA_ProcPlmnSpecialSelCnf(TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* ת���û�����PLMN�ַ�ΪPLMN ID */
    ulRet = MMA_FormatPlmnStr2PlmnId(&stPlmn,
                                      pstPlmnSpecialSelMsg->stPlmnUserSel.ucFormatType,
                                      pstPlmnSpecialSelMsg->stPlmnUserSel.usOperNameLen,
                                      pstPlmnSpecialSelMsg->stPlmnUserSel.ucOperName);
    if( VOS_TRUE == ulRet)
    {
        MMA_PlmnId2NasStyle(&stPlmn);

        /* ͨ��ԭ�е�TAF_PH_EVT_PLMN_SEL_CNF��Ϣ��ָ���ѽ�����͸�AT */
        MMA_PhonePlmnUserSel(pstPlmnSpecialSelMsg->stCtrl.usClientId, pstPlmnSpecialSelMsg->stCtrl.ucOpId, stPlmn, pstPlmnSpecialSelMsg->stPlmnUserSel.enAccessMode, TAF_PLMN_RESELETION_MANUAL);
    }
    else
    {
        /*������*/
        TAF_MMA_ProcPlmnSpecialSelCnf(TAF_ERR_PARA_ERROR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcPlmnAutoReselReq_Main
 ��������  : ����PLMN�Զ���ѡ����
 �������  : ulOpID   -- operation ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��12��26��
   ��    ��   : y00245242
   �޸�����   : �½�
*****************************************************************************/
VOS_VOID TAF_MMA_ProcPlmnAutoReselReq_Main(
    VOS_UINT32                          ulOpID
)
{
    VOS_UINT32                            ulRet;
    TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8 enAutoPlmnSelUser;

    TAF_INFO_LOG1(WUEPS_PID_MMA,
                  "TAF_MMA_ProcPlmnAutoReselReq_Main: current ulFsmState",
                  g_StatusContext.ulFsmState);

    enAutoPlmnSelUser = TAF_MMA_GetAutoPlmnSelUser();

    /* svlte nv��������ػ�״̬����cops */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        (VOS_VOID)TAF_MMA_PlmnReselectAutoReq_PowerOff(ulOpID);

        return;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_FALSE == TAF_SDC_IsConfigCLMode())       // liuqg ΪFALSE��ʱ��Ӧ�þ���LTE, ��ô1X ʱ����Ҫ�ж������������
#endif
    {
        /* PLMN_RESEL״̬������������쳣 */
        /* ��ǰ���ڽ���6F15�ļ��������Զ����� */
        if ((STA_FSM_PLMN_RESEL                      == g_StatusContext.ulFsmState)
         && (TAF_MMA_AUTO_PLMN_SEL_USER_USIM_REFRESH == enAutoPlmnSelUser))
        {
            TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcPlmnAutoReselReq_Main: 6F15 file trigered auto search!");

            /* ��¼ΪAT������Զ��������յ�CNF֮����Ҫ���û��ظ���� */
            TAF_MMA_SetAutoPlmnSelUser(TAF_MMA_AUTO_PLMN_SEL_USER_AT); // liuqg ���ڽ���6F15�ļ��������Զ�����, Ϊʲô��¼ΪAT������Զ�����

            /* ��¼��ǰ�Ĳ������̱�ʶ�� */
            g_StatusContext.ulCurOpId = ulOpID;

            return;
        }
    }

    if ( VOS_FALSE == (g_StatusContext.ulFsmState & STA_FSM_ENABLE) )
    {
        /* �������ENABLE״̬�����ش��� */
        TAF_MMA_ProcPlmnAutoReselCnf(TAF_ERR_PHONE_MSG_UNMATCH);

        return;
    }

    ulRet = TAF_MMA_SndMsccPlmnUserReselReq(NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO);

    if ( VOS_ERR == ulRet )
    {
        return;
    }

    /* ��¼AT������Զ��������� */
    TAF_MMA_SetAutoPlmnSelUser(TAF_MMA_AUTO_PLMN_SEL_USER_AT);

    /* ��¼��ǰ�Ĳ������̱�ʶ�� */
    g_StatusContext.ulCurOpId = ulOpID;

    /* ��¼PLMN�������� */
    g_StatusContext.ucReselMode = NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO;

    /* ����PLMN_RESEL״̬��־�� */
    g_StatusContext.ulFsmState = STA_FSM_PLMN_RESEL;

    TAF_INFO_LOG1(WUEPS_PID_MMA,
                  "TAF_MMA_ProcPlmnAutoReselReq_Main: new ulFsmState = ",
                  g_StatusContext.ulFsmState);

    /* ����������ʱ��TI_TAF_MMA_WAIT_MSCC_PLMNAUTORESEL_SET_CNF */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_PLMN_AUTO_RESEL_CNF, TI_TAF_MMA_WAIT_MSCC_PLMN_AUTO_RESEL_SET_CNF_LEN);

    /* ������״̬�Ĳ������̱�ʶ�� */
    g_StatusContext.aFsmSub[0].ulOpId = ulOpID;

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvPlmnAutoReselReq_Main
 ��������  : PLMN��ѡ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��3��25��
    ��    ��   : f00279542
    �޸�����   : CDMA Iteration 11 �ع��޸�

 2.��    ��   : 2015��12��25��
   ��    ��   : y00245242
   �޸�����   : CLģʽ�£����������������Կ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvPlmnAutoReselReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucError;
    TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU   *pstPlmnReselMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstPlmnReselMsg = (TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU *)pstMsg;

    /* ���g_stTafMmaCtx.astMmaOperCtx��TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ���ͽṹ���ڱ�ʹ�� */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ))
    {
        /* ֱ�ӻظ�RESEL����ʧ�� */
        TAF_MMA_SndPlmnAutoReselCnf(&pstPlmnReselMsg->stCtrl, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* �Ҳ���δ��ʹ�õģ��ظ�ʧ�� */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndPlmnAutoReselCnf(&pstPlmnReselMsg->stCtrl, TAF_MMA_APP_OPER_RESULT_FAILURE);
        return VOS_TRUE;
    }

    /* ����һ��g_stTafMmaCtx.astMmaOperCtx����Ӧ���� */
    TAF_MMA_SetOperCtx(pstPlmnReselMsg->stCtrl,
                       TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ, ucCtxIndex);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_FALSE == TAF_SDC_IsConfigCLMode())
#endif
    {
        ucError = TAF_ERR_NO_ERROR;
        ucError = MMA_CheckUsimStatusForPlmnSel();
        if(TAF_ERR_NO_ERROR != ucError)
        {
            MMA_WARNINGLOG("TAF_MMA_RcvPlmnAutoReselReq_Main():WARNING:UsimStatus Error!");
            /*������*/
            TAF_MMA_ProcPlmnAutoReselCnf(ucError);
            return VOS_TRUE;
        }
    }

    TAF_MMA_ProcPlmnAutoReselReq_Main(pstPlmnReselMsg->stCtrl.ucOpId);

    return VOS_TRUE;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


