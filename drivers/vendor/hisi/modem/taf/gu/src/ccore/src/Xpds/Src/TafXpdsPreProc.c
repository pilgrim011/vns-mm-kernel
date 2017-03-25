/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXpdsPreProc.c
  �� �� ��   : ����
  ��    ��   : g00256031
  ��������   : 2015��08��26��
  ��������   : XPDSԤ״̬���¼�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��08��26��
    ��    ��   : g00256031
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXpdsPreProc.h"
#include "TafXpdsCtx.h"
#include "TafSdcCtx.h"
#include "TafXpdsSndAt.h"
#include "TafXpdsMntn.h"
#include "TafXpdsDecode.h"
#include "TafXpdsSndInternalMsg.h"
#include "TafXpdsSndCas.h"
#include "TafXpdsXsmsInterface.h"
#include "TafXpdsSndXsms.h"
#include "TafXpdsFsmPdeProc.h"
#include "TafXpdsFsmMainTbl.h"
#include "TafXpdsCommFunc.h"



#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_PRE_PROC_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
TAF_XPDS_DOWN_DATA_CTRL_STRU g_stTafXpdsDownCtrlPreProc = {0};


/*****************************************************************************
  3 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvAtGpsStartReq_PreProc
 ��������  : Ԥ����^CAGPSSTART����
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��16��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsStartReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_START_REQ_STRU         *pstMsgStartReq;
    XPDS_AT_RESULT_CNF_STRU             stStartCnf;
    VOS_UINT32                          ulCurState;

    ulCurState = TAF_XPDS_GetFsmTopState();

    /* ��ǰ�ڳ�ʼ��״̬�򽻸���ʼ��״̬������ */
    if ((TAF_XPDS_FSM_L1_MAIN == TAF_XPDS_GetCurrFsmId())
     && (TAF_XPDS_L1_STA_INIT == ulCurState))
    {
        return VOS_FALSE;
    }

    /* �ֲ�������ʼ�� */
    pstMsgStartReq  = (AT_XPDS_GPS_START_REQ_STRU *)pstMsg;

    /* Ĭ�ϻظ�ʧ�� */
    PS_MEM_SET(&stStartCnf, 0x0, sizeof(stStartCnf));
    stStartCnf.enResult = XPDS_AT_RESULT_ERROR;

    TAF_XPDS_SndAtMsg(&pstMsgStartReq->stAppCtrl,
                      ID_XPDS_AT_GPS_START_CNF,
                      sizeof(stStartCnf),
                      (VOS_UINT8*)&stStartCnf);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvAtGpsCfgMpcAddrReq_PreProc
 ��������  : Ԥ����^CAGPSCFGMPCADDR����
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��16��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsCfgMpcAddrReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_CFG_MPC_ADDR_REQ_STRU  *pstMsgCfgMpcAddReq;
    XPDS_AT_RESULT_CNF_STRU             stMpcAddrCnf;
    VOS_UINT32                          ulCurState;

    ulCurState = TAF_XPDS_GetFsmTopState();

    /* ��ǰ�ڳ�ʼ��״̬�򽻸���ʼ��״̬������ */
    if ((TAF_XPDS_FSM_L1_MAIN == TAF_XPDS_GetCurrFsmId())
     && (TAF_XPDS_L1_STA_INIT == ulCurState))
    {
        return VOS_FALSE;
    }

    /* �ֲ�������ʼ�� */
    pstMsgCfgMpcAddReq  = (AT_XPDS_GPS_CFG_MPC_ADDR_REQ_STRU *)pstMsg;

    /* ��Ϣ����ɹ�����AT�ظ��ɹ� */
    PS_MEM_SET(&stMpcAddrCnf, 0x0, sizeof(stMpcAddrCnf));
    stMpcAddrCnf.enResult = XPDS_AT_RESULT_ERROR;

    TAF_XPDS_SndAtMsg(&pstMsgCfgMpcAddReq->stAppCtrl,
                     ID_XPDS_AT_GPS_CFG_MPC_ADDR_CNF,
                     sizeof(stMpcAddrCnf),
                     (VOS_UINT8*)&stMpcAddrCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvAtGpsCfgPdeAddrReq_PreProc
 ��������  : Ԥ����^CAGPSCFGPDEADDR����
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��16��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsCfgPdeAddrReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_CFG_PDE_ADDR_REQ_STRU  *pstAMsgCfgPdeAddrReq;
    XPDS_AT_RESULT_CNF_STRU             stPdeAddrCnf;
    VOS_UINT32                          ulCurState;

    ulCurState = TAF_XPDS_GetFsmTopState();

    /* ��ǰ�ڳ�ʼ��״̬�򽻸���ʼ��״̬������ */
    if ((TAF_XPDS_FSM_L1_MAIN == TAF_XPDS_GetCurrFsmId())
     && (TAF_XPDS_L1_STA_INIT == ulCurState))
    {
        return VOS_FALSE;
    }

    /* �ֲ�������ʼ�� */
    pstAMsgCfgPdeAddrReq  = (AT_XPDS_GPS_CFG_PDE_ADDR_REQ_STRU *)pstMsg;

    PS_MEM_SET(&stPdeAddrCnf, 0x0, sizeof(stPdeAddrCnf));
    stPdeAddrCnf.enResult = XPDS_AT_RESULT_ERROR;

    /* ��Ϣ������ɣ���AT�ظ���� */
    TAF_XPDS_SndAtMsg(&pstAMsgCfgPdeAddrReq->stAppCtrl,
                     ID_XPDS_AT_GPS_CFG_PDE_ADDR_CNF,
                     sizeof(stPdeAddrCnf),
                     (VOS_UINT8*)&stPdeAddrCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvAtGpsCfgPositionModeReq_PreProc
 ��������  : Ԥ����^CAGPSCFGPOSMODE����
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��16��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsCfgPositionModeReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_CFG_POSITION_MODE_REQ_STRU                 *pstMsgCfgPosModeReq;
    XPDS_AT_RESULT_CNF_STRU                                 stCfgModeCnf;
    VOS_UINT32                                              ulCurState;

    ulCurState = TAF_XPDS_GetFsmTopState();

    /* ��ǰ�ڳ�ʼ��״̬�򽻸���ʼ��״̬������ */
    if ((TAF_XPDS_FSM_L1_MAIN == TAF_XPDS_GetCurrFsmId())
     && (TAF_XPDS_L1_STA_INIT == ulCurState))
    {
        return VOS_FALSE;
    }

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stCfgModeCnf, 0x0, sizeof(stCfgModeCnf));
    stCfgModeCnf.enResult = XPDS_AT_RESULT_ERROR;

    pstMsgCfgPosModeReq  = (AT_XPDS_GPS_CFG_POSITION_MODE_REQ_STRU* )pstMsg;

    /* ��Ϣ������ɣ���AT�ظ���� */
    TAF_XPDS_SndAtMsg(&pstMsgCfgPosModeReq->stAppCtrl,
                     ID_XPDS_AT_GPS_CFG_MODE_CNF,
                     sizeof(stCfgModeCnf),
                     (VOS_UINT8*)&stCfgModeCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvAtGpsQryRefLocInfoReq_PreProc
 ��������  : Ԥ����^CAGPSCFGPOSMODE����
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��16��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsQryRefLocInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_QRY_REFLOC_INFO_REQ_STRU                   *pstMsgQryRefLocReq;
    XPDS_AT_GPS_REFLOC_INFO_STRU                            stXpdsAtRefloc;
    TAF_SDC_1X_SYS_INFO_STRU                               *pst1XSys;
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;

    /* �ֲ�������ʼ�� */
    pstMsgQryRefLocReq  = (AT_XPDS_GPS_QRY_REFLOC_INFO_REQ_STRU*)pstMsg;

    PS_MEM_SET(&stXpdsAtRefloc, 0, sizeof(XPDS_AT_GPS_REFLOC_INFO_STRU));
    stXpdsAtRefloc.ucValidRefLoc = 0; /* 0: Not valid */

    enSysMode = TAF_SDC_GetSysMode();

    if ((TAF_SDC_SYS_MODE_CDMA_1X == enSysMode)
     || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))
    {
        /* 2: Valid Time Zone and BS Location. */
        stXpdsAtRefloc.ucValidRefLoc = 2;

        pst1XSys = TAF_SDC_Get1xSysInfo();

        stXpdsAtRefloc.usSid       = (VOS_UINT16)pst1XSys->lSid;
        stXpdsAtRefloc.usNid       = (VOS_UINT16)pst1XSys->lNid;
        stXpdsAtRefloc.usBsid      = (VOS_UINT16)pst1XSys->stBaseStationInfo.usBaseId;

        /* stReflocCnf.ulTzLat, stReflocCnf.ulTzLongĿǰ����Ϊ0 */
        stXpdsAtRefloc.ulTzLat     = 0;
        stXpdsAtRefloc.ulTzLong    = 0;

        stXpdsAtRefloc.ulBslat     = (VOS_UINT32)pst1XSys->stBaseStationInfo.lBaseLatitude;
        stXpdsAtRefloc.ulBslong    = (VOS_UINT32)pst1XSys->stBaseStationInfo.lBaseLongitude;
    }

    TAF_XPDS_SndAtGpsReflocInfoCnf(&(pstMsgQryRefLocReq->stAppCtrl), &stXpdsAtRefloc);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvAtGpsQryTimeInfoReq_PreProc
 ��������  : Ԥ�����յ�AT������ID_AT_XPDS_SYNC_TIME_REQ��Ϣ������
 �������  : pstMsg  -- ��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��10��
    ��    ��   : d00212987
    �޸�����   : AGPS����1����
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsQryTimeInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_QRY_TIME_INFO_REQ_STRU *pstMsgQryTimeReq;
    AT_XPDS_REPLY_SYNC_TIME_ENUM_UINT8  enSyncTimeActionType;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;
    VOS_UINT32                          ulCurState;

    /* �ֲ�������ʼ�� */
    pstMsgQryTimeReq  = (AT_XPDS_GPS_QRY_TIME_INFO_REQ_STRU *)pstMsg;

    enSyncTimeActionType = pstMsgQryTimeReq->enActionType;

    ulCurState = TAF_XPDS_GetFsmTopState();

    /* ���潻��ͨ����ClientId */
    TAF_XPDS_SetGpsClientId(pstMsgQryTimeReq->stAppCtrl.usClientId);

    /* ��ǰ�ڳ�ʼ��״̬�򽻸���ʼ��״̬������ */
    if ((TAF_XPDS_FSM_L1_MAIN == TAF_XPDS_GetCurrFsmId())
     && (TAF_XPDS_L1_STA_INIT == ulCurState)
     && (AT_XPDS_REPLY_SYNC_TIME_AND_ASSIST_DATA == enSyncTimeActionType))
    {
        return VOS_FALSE;
    }

    if ((AT_XPDS_REPLY_SYNC_TIME_INFO            == enSyncTimeActionType)
     || (AT_XPDS_REPLY_SYNC_TIME_AND_ASSIST_DATA == enSyncTimeActionType))
    {
        enSysMode = TAF_SDC_GetSysMode();

        TAF_XPDS_SndCasSyncTimeReq(enSysMode);

        return VOS_TRUE;
    }

    if (AT_XPDS_REPLY_FORCE_SYNC_TIME == enSyncTimeActionType)
    {
        /* �ܽ��麸��⣬ǿ�ƴ������壬��ȡsynctime */
        TAF_XPDS_SndCasSyncTimeReq(TAF_SDC_SYS_MODE_BUTT);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvAtApServerBindStatusInd_PreProc
 ��������  : Ԥ����״̬�յ�AP���Ͷ����ķ�����Bind Cnf�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��8��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtApServerBindStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *pstMsgBindStatusInd;

    pstMsgBindStatusInd = (AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *)pstMsg;

    if (TAF_XPDS_FSM_LINK_CTRL == TAF_XPDS_GetCurrFsmId())
    {
        /* ��Ҫ���뽨��״̬����һ������ */
        return VOS_FALSE;
    }

    if (AT_XPDS_SERVER_MODE_MPC == pstMsgBindStatusInd->enServerMode)
    {
        /* ����MPC��ǰ��·״̬ */
        TAF_XPDS_SetMpcServerStatus(pstMsgBindStatusInd->enBindStatus);

        /* MPC���ݽ���״̬���У��յ�Server�쳣�����Ĵ��� */
        if ((TAF_XPDS_FSM_MPC_PROC == TAF_XPDS_GetCurrFsmId())
         && (AT_XPDS_SERVER_BIND_STATUS_IDLE == pstMsgBindStatusInd->enBindStatus))
        {
            TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(TAF_XPDS_PROC_RSLT_UP_MPC_DISCONNECT);
        }
    }

    if (AT_XPDS_SERVER_MODE_PDE == pstMsgBindStatusInd->enServerMode)
    {
        /* ����PDE��ǰ��·״̬ */
        TAF_XPDS_SetPdeServerStatus(pstMsgBindStatusInd->enBindStatus);

        /* PDE���ݽ���״̬���У��յ�Server�쳣�����Ĵ��� */
        if ((TAF_XPDS_FSM_PDE_PROC == TAF_XPDS_GetCurrFsmId())
         && (AT_XPDS_SERVER_BIND_STATUS_IDLE == pstMsgBindStatusInd->enBindStatus))
        {
            TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(TAF_XPDS_PROC_RSLT_UP_PDE_DISCONNECT);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvAtGpsStopReq_PreProc
 ��������  : �յ��û�Stop Agps���̵�Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��9��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsStopReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(TAF_XPDS_PROC_RSLT_AT_STOP);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvCasTimeSyncInd_PreProc
 ��������  : XPDS�յ�Cas��ȡSync Timer���
 �������  : pMsg : CAS�ϱ�sync time���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��10��
    ��    ��   : d00212987
    �޸�����   : AGPS����1����
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvCasTimeSyncInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_XPDS_TIME_SYNC_IND_STRU        *pstRcvSyncTime = VOS_NULL_PTR;

    pstRcvSyncTime = (CAS_XPDS_TIME_SYNC_IND_STRU*)pstMsg;

    TAF_XPDS_SndAtGpsTimeSyncInfo(pstRcvSyncTime);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvCasRefLocInd
 ��������  : XPDS�յ�CAS��ȡλ����Ϣ֪ͨ
 �������  : pMsg : CAS�ϱ��ο�λ��IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��10��
    ��    ��   : d00212987
    �޸�����   : AGPS����1����
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvCasRefLocInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_XPDS_REF_LOC_IND_STRU                         *pstRefLocInd;
    TAF_XPDS_CAS_RPT_PILOT_BUFF_STRU                  *pstCasRptPilotBuff;
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU        *pstProvPp;
    VOS_UINT8                                          ucPilotStrgth;
    VOS_UINT32                                         ulIndex = 0;
    VOS_UINT32                                         ulTempCount = 0;
    VOS_UINT16                                         i;

    pstProvPp = &(TAF_XPDS_GetPublicDataAddr()->stPilotInfo);

    pstCasRptPilotBuff = &(pstProvPp->stCasRptPilotBuff);

    /* �洢�ϱ�pilot���� */
    pstRefLocInd = (CAS_XPDS_REF_LOC_IND_STRU*)pstMsg;

    if (XPDS_CAS_MAX_NEIGHBOR_NUM < pstRefLocInd->usPilotNum)
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvCasRefLocInd_PreProc: PilotNum > 50!");

        pstRefLocInd->usPilotNum   = XPDS_CAS_MAX_NEIGHBOR_NUM;
    }

    /* ���pilot����� */
    pstProvPp->ulTimeRefMS          = pstRefLocInd->ulMsRefTime;
    pstProvPp->sMobSysTOffst        = pstRefLocInd->sMsSysTimeOffset;
    pstProvPp->usRefPn              = pstRefLocInd->usRefPN;

    pstProvPp->ucRefPilotStrgth     = TAF_XPDS_FormatPnStrength(pstRefLocInd->sRefPnStrength);

    pstProvPp->ucBandClass          = (VOS_UINT8)pstRefLocInd->usBandClass;
    pstProvPp->usCdmaFreq           = pstRefLocInd->usCdmaFreq;

    pstProvPp->usBaseId             = TAF_SDC_Get1xBaseId();
    pstProvPp->usSID                = (VOS_UINT16)TAF_SDC_Get1xSid();
    pstProvPp->usNID                = (VOS_UINT16)TAF_SDC_Get1xNid();

    /* CAS�ϱ���1/8���� */
    pstProvPp->ucTotalRxPow         = TAF_XPDS_FormatServFreqRssi(pstRefLocInd->sServFreqRssi);

    pstProvPp->ucNumOfPilotP        = (VOS_UINT8)pstRefLocInd->usPilotNum;

    /* ����Э����ֶε�ȡֵ��1/16����-512��511.9375,�����˷�Χ������Ч */
    if ((-8192 > pstProvPp->sMobSysTOffst) || (8191 < pstProvPp->sMobSysTOffst))
    {
        pstProvPp->ucOffsetIncl = 0; /* ���ø�ֵ��Ч */
    }
    else
    {
        pstProvPp->ucOffsetIncl = 1;
    }

    /* �洢pilot measure */
    for (i=0; i<pstRefLocInd->usPilotNum; i++)
    {
#if 0
        if (   ( 0 != pstRefLocInd->stPilotMeasInfo[i].usPilotPN)
            && ( 8 != pstRefLocInd->stPilotMeasInfo[i].usPilotPN)
            && ( 16 != pstRefLocInd->stPilotMeasInfo[i].usPilotPN)
            )
        {
            continue;
        }
#endif
        ucPilotStrgth = TAF_XPDS_FormatPnStrength(pstRefLocInd->stPilotMeasInfo[i].sPnStrength);

        /* �����һ���ϱ�ǰ10������ǿ����ǿ����Ϊ�ϱ��ο�����ֵ */
        if (TAF_XPDS_RL_PHASE_PILREC_MAX > ulTempCount)
        {
            pstProvPp->astPilotRec[ulTempCount].ucPilotStrgth  = ucPilotStrgth;
            pstProvPp->astPilotRec[ulTempCount].usPilotPN      = pstRefLocInd->stPilotMeasInfo[i].usPilotPN;
            pstProvPp->astPilotRec[ulTempCount].ulPilotPnPhase = pstRefLocInd->stPilotMeasInfo[i].ulPnPhase;

            ulTempCount++;
        }

        /* ֻ���CAS����ϱ���4s���� */
        ulIndex = pstCasRptPilotBuff->ulPilotMeasNum % TAF_XPDS_PILOT_MEAS_BUFF_MAX;

        /* ����ȫ�ֱ����� */
        pstCasRptPilotBuff->astPilotMeasInfo[ulIndex].usPilotPN   = pstRefLocInd->stPilotMeasInfo[i].usPilotPN;
        pstCasRptPilotBuff->astPilotMeasInfo[ulIndex].sPnStrength = ucPilotStrgth;
        pstCasRptPilotBuff->astPilotMeasInfo[ulIndex].ulPnPhase   = pstRefLocInd->stPilotMeasInfo[i].ulPnPhase;

        pstCasRptPilotBuff->ulPilotMeasNum++;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_CheckForwardData_PreProc
 ��������  : ���MPC/PDE��������
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��16��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_CheckForwardData_PreProc(
    AT_XPDS_AP_FORWARD_DATA_IND_STRU   *pstDownDataInd
)
{
    TAF_XPDS_UP_LINK_STATUS_ENUM_UINT8  enCurUpLinkStatus;

    enCurUpLinkStatus = TAF_XPDS_GetUpLinkStatus();

    if (AT_XPDS_SERVER_MODE_MPC == pstDownDataInd->enServerMode)
    {
        if ((TAF_XPDS_UP_LINK_MPC_CONNECTED == enCurUpLinkStatus)
         || (TAF_XPDS_UP_LINK_MPC_PDE_BOTH_CONNECTED == enCurUpLinkStatus))
        {
            return VOS_OK;
        }
    }

    if (AT_XPDS_SERVER_MODE_PDE == pstDownDataInd->enServerMode)
    {
        if ((TAF_XPDS_UP_LINK_PDE_CONNECTED == enCurUpLinkStatus)
         || (TAF_XPDS_UP_LINK_MPC_PDE_BOTH_CONNECTED == enCurUpLinkStatus))
        {
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvApForwardDataInd_PreProc
 ��������  : XPDS����ID_AT_XPDS_AP_FORWARD_DATA_IND��Ϣ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvApForwardDataInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_AP_FORWARD_DATA_IND_STRU   *pstMsgFwdDataInd;

    pstMsgFwdDataInd  = (AT_XPDS_AP_FORWARD_DATA_IND_STRU*)(pstMsg);

    if (VOS_OK != TAF_XPDS_CheckForwardData_PreProc(pstMsgFwdDataInd))
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvApForwardDataInd_PreProc : TAF_XPDS_CheckForwardData_PreProc error");

        return VOS_TRUE;
    }

    if (1 == pstMsgFwdDataInd->ulCurNum)
    {
        if (VOS_NULL_PTR != g_stTafXpdsDownCtrlPreProc.pucData)
        {
            (VOS_VOID)PS_MEM_FREE(UEPS_PID_XPDS, g_stTafXpdsDownCtrlPreProc.pucData);
        }

        (VOS_VOID)PS_MEM_SET(&g_stTafXpdsDownCtrlPreProc, 0, sizeof(g_stTafXpdsDownCtrlPreProc));

        g_stTafXpdsDownCtrlPreProc.pucData = (VOS_UINT8*)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                                      TAF_XPDS_ATDOWN_MAX_LEN);

        g_stTafXpdsDownCtrlPreProc.ulTotalNum = pstMsgFwdDataInd->ulTotalNum;
    }

    if ((pstMsgFwdDataInd->ulCurNum != g_stTafXpdsDownCtrlPreProc.ulCurIndex + 1)
      ||(pstMsgFwdDataInd->ulDataLen + g_stTafXpdsDownCtrlPreProc.ulTotalLen >= TAF_XPDS_ATDOWN_MAX_LEN)
      ||(g_stTafXpdsDownCtrlPreProc.ulTotalNum != pstMsgFwdDataInd->ulTotalNum))
    {
        if (VOS_NULL_PTR != g_stTafXpdsDownCtrlPreProc.pucData)
        {
            (VOS_VOID)PS_MEM_FREE(UEPS_PID_XPDS, g_stTafXpdsDownCtrlPreProc.pucData);
        }

        (VOS_VOID)PS_MEM_SET(&g_stTafXpdsDownCtrlPreProc, 0, sizeof(g_stTafXpdsDownCtrlPreProc));

        return VOS_TRUE;
    }

    (VOS_VOID)PS_MEM_CPY(&g_stTafXpdsDownCtrlPreProc.pucData[g_stTafXpdsDownCtrlPreProc.ulTotalLen],
                         pstMsgFwdDataInd->aucData,
                         pstMsgFwdDataInd->ulDataLen);

    g_stTafXpdsDownCtrlPreProc.ulCurIndex = pstMsgFwdDataInd->ulCurNum;

    g_stTafXpdsDownCtrlPreProc.ulTotalLen += pstMsgFwdDataInd->ulDataLen;

    if (pstMsgFwdDataInd->ulCurNum != pstMsgFwdDataInd->ulTotalNum)
    {
        return VOS_TRUE;
    }

    if (AT_XPDS_SERVER_MODE_MPC == pstMsgFwdDataInd->enServerMode)
    {
        /* MPC ���ݴ��� */
        TAF_XPDS_ProcForwardMpcMsg_PreProc(g_stTafXpdsDownCtrlPreProc.pucData,
                                           g_stTafXpdsDownCtrlPreProc.ulTotalLen);
    }

    if (AT_XPDS_SERVER_MODE_PDE == pstMsgFwdDataInd->enServerMode)
    {
        /* PDE ���ݴ��� */
        TAF_XPDS_ProcForwardPdeMsg_PreProc(g_stTafXpdsDownCtrlPreProc.pucData,
                                           g_stTafXpdsDownCtrlPreProc.ulTotalLen);
    }

    (VOS_VOID)PS_MEM_FREE(UEPS_PID_XPDS, g_stTafXpdsDownCtrlPreProc.pucData);

    (VOS_VOID)PS_MEM_SET(&g_stTafXpdsDownCtrlPreProc, 0, sizeof(g_stTafXpdsDownCtrlPreProc));

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_ProcForwardMpcMsg_PreProc
 ��������  :
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��16��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_ProcForwardMpcMsg_PreProc(
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulDataLen
)
{
    switch (pucData[1])
    {
        case TAF_XPDS_MPC_MS_START_POS_RSP:
            TAF_XPDS_RcvAtMpcStartPosRespHandle_PreProc(ulDataLen, pucData);

            TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_TCP_MPC_FL_START_POS_RSP);

            break;

        case TAF_XPDS_MPC_MS_POS_REPORT_RSP:
            TAF_XPDS_RcvAtMpcPosReportRspHandle_PreProc(ulDataLen, pucData);

            TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_TCP_MPC_FL_POS_REPORT_RSP);

            break;

        default:
            XPDS_ERROR_LOG("TAF_XPDS_RcvAtMpcMsgHandle:err msg type");
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvAtMpcStartPosRespHandle
 ��������  : XPDS����MPC����
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��16��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_RcvAtMpcStartPosRespHandle_PreProc(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData
)
{
    TAF_XPDS_MPC_START_POS_RSP_STRU     stStartPosRsp;

    PS_MEM_SET(&stStartPosRsp, 0, sizeof(TAF_XPDS_MPC_START_POS_RSP_STRU));

    if (VOS_ERR == TAF_XPDS_DecodeMpcStartPosRsp(ulDataLen,
                                                 pucData,
                                                 &stStartPosRsp))
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvAtMpcStartPosRespHandle:TAF_XPDS_DecodeMpcStartPosRsp err");
        return;
    }

    /* ��Ϣ�洢 */
    PS_MEM_CPY(&(TAF_XPDS_GetMpcCtxAddr()->stStartPosRsp),
               &(stStartPosRsp),
               sizeof(stStartPosRsp));

    TAF_XPDS_SndInternalMpcStartPosResp(&stStartPosRsp);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvAtMpPosReportRspHandle
 ��������  : XPDS����MPC����
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��16��
    ��    ��   : C00299064
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_RcvAtMpcPosReportRspHandle_PreProc(
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucData
)
{
    TAF_XPDS_MPC_POS_REPORT_RSP_STRU    stPosReportRsp;

    PS_MEM_SET(&stPosReportRsp, 0, sizeof(TAF_XPDS_MPC_POS_REPORT_RSP_STRU));

    if (VOS_ERR == TAF_XPDS_DecodeMpcPosReportRsp(ulDataLen,
                                                  pucData,
                                                  &stPosReportRsp))
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvAtMpcPosReportRspHandle:TAF_XPDS_DecodeMpcStartPosRsp err");
        return;
    }

    /* ��Ϣ�洢 */
    PS_MEM_CPY(&(TAF_XPDS_GetMpcCtxAddr()->stPosReportRsp),
               &stPosReportRsp,
               sizeof(stPosReportRsp));

    /* ��Ϣ���� �ڵ���2���� */

    TAF_XPDS_SndInternalMpcPosReportResp(&stPosReportRsp);

    return;
}



/*****************************************************************************
 �� �� ��  : TAF_XPDS_ProcForwardPdeMsg_PreProc
 ��������  : Process Forward Msg from PDE
 �������  : VOS_UINT8                          *pucMsgBuf
             VOS_UINT32                          ulTotLength
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XPDS_ProcForwardPdeMsg_PreProc(
    VOS_UINT8                          *pucMsgBuf,
    VOS_UINT32                          ulTotLength
)
{
    VOS_UINT32                          ulPdeDataMask;

    ulPdeDataMask = 0;

    if (TAF_XPDS_USER_PLANE == TAF_XPDS_GetAgpsCfg()->enCallType)
    {
        /* Decode User Plane Forward Pde Msg */
        if (VOS_OK != TAF_XPDS_DecodeForwardPdeData(pucMsgBuf, ulTotLength, &ulPdeDataMask))
        {
            return;
        }
    }
    else
    {
        /* Decode Control Plane Forward Pde Msg */
        if (VOS_OK != TAF_XPDS_DecodeOnePdeMsg(pucMsgBuf, &ulPdeDataMask))
        {
            return;
        }
    }

    TAF_XPDS_MNTN_TraceForwardMsgInfoIndMsg(ulPdeDataMask);

    /* EPH��ALM���ݵ������Ԥ�����д������յ����еķְ�֮�󣬷�������ָʾ��Ϣ */
    if (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_EPH
            == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_EPH & ulPdeDataMask))
    {
        TAF_XPDS_ProcEphData_PreProc();

        ulPdeDataMask &= ~TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_EPH;
    }

    if (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_ALM
            == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_ALM & ulPdeDataMask))
    {
        TAF_XPDS_ProcAlmData_PreProc();

        ulPdeDataMask &= ~TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_ALM;
    }

    if (0 != ulPdeDataMask)
    {
        TAF_XPDS_SndInternalForwardPdeDataInd(ulPdeDataMask ,TAF_XPDS_GetAgpsCfg()->enCallType);
    }

    return;

}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_ProcEphData_PreProc
 ��������  : �����PDE���������յ���EPH����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XPDS_ProcEphData_PreProc(VOS_VOID)
{
    VOS_UINT32                                              ulPdeDataMask;
    TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU                      *pstProvEph = VOS_NULL_PTR;

    pstProvEph = &(TAF_XPDS_GetPdePublicData()->stProvGpsEph);

    /* �յ�����PART֮����EPH�����ڲ���Ϣ */
    if (pstProvEph->ucPartNum == pstProvEph->ucTotalParts)
    {
        ulPdeDataMask = TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_EPH;

        TAF_XPDS_SndInternalForwardPdeDataInd(ulPdeDataMask , TAF_XPDS_GetAgpsCfg()->enCallType);
    }
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_ProcAlmData_PreProc
 ��������  : �����PDE���������յ���ALM����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XPDS_ProcAlmData_PreProc(VOS_VOID)
{
    VOS_UINT32                                              ulPdeDataMask;
    TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU                      *pstProvAlm = VOS_NULL_PTR;

    pstProvAlm = &(TAF_XPDS_GetPdePublicData()->stProvGpsAlm);

    /* �յ�����PART֮����ALM�����ڲ���Ϣ */
    if (pstProvAlm->ucPartNum == pstProvAlm->ucTotalParts)
    {
        ulPdeDataMask = TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_ALM;

        TAF_XPDS_SndInternalForwardPdeDataInd(ulPdeDataMask ,TAF_XPDS_GetAgpsCfg()->enCallType);
    }
}



/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvXsmsRcvInd_PreProc
 ��������  : Ԥ����״̬�յ�XSMS��Ϣ������
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �Ѵ���
             VOS_FALSE - δ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��9��6��
    ��    ��   : y00174758
    �޸�����   : AGPS����2: �ж�MPC�·����ŵİ汾
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXsmsRcvInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XSMS_XPDS_REV_IND_STRU                             *pstXsmsRcvInd;
    TAF_XPDS_RCV_XSMS_MSG_STRU                              stXsmsMsg;
    VOS_UINT32                                              ulCurrFsmId;
    VOS_UINT32                                              ulCurState;
    TAF_XPDS_XSMS_MSG_DECODE_RSLT_ENUM_UINT8                enDecodeRslt;

    pstXsmsRcvInd           = (TAF_XSMS_XPDS_REV_IND_STRU*)pstMsg;

    PS_MEM_SET(&stXsmsMsg, 0, sizeof(TAF_XPDS_RCV_XSMS_MSG_STRU));

    if (ID_XSMS_XPDS_RCV_IND == pstXsmsRcvInd->enMsgName)
    {

        /* �������෢��������Ϣ */
        enDecodeRslt = TAF_XPDS_DecodeXsmsRcvMsg(pstXsmsRcvInd->usDataLen,
                                                 pstXsmsRcvInd->aucData,
                                                 &stXsmsMsg);

        if (TAF_XPDS_XSMS_MSG_DECODE_RSLT_ERROR == enDecodeRslt)
        {
            XPDS_ERROR_LOG("TAF_XPDS_RcvXsmsRcvInd_PreProc:TAF_XPDS_DecodeXsmsRcvMsg error");
            return VOS_TRUE;
        }

        /* �������Դ��ַ */
        PS_MEM_CPY(&(TAF_XPDS_GetMpcCtxAddr()->stXsmsAddr),
                   &pstXsmsRcvInd->stXsmsAddr,
                   sizeof(TAF_XSMS_ADDR_STRU));

        /*
           �й���������
           LBS-05004  [��ѡ]   ���� SMS�� MPC���ն˵���Ϣ����
           3�����ն��յ�һ��"Version"��Ϊ'00000010'��"65001"MT ����Ϣʱ���ն�Ӧ������ԭ����д���
           ����ն�û�д��ڶ�λ�Ự�У��ն�Ӧ�ظ�һ������ MO SMS �� Reject Positioning Request ��Ϣ��
           ����Ϣָʾ�ն˲�֧�������յ���Э��汾����ͨ�� MO SMS�е�"Version"������ն�ֻ֧��Э��汾00000010��
           ����ն�������һ����λ�Ự�У��ն�Ӧ�򵥺��Ը� MT SMS��
        */

        if (TAF_XPDS_XSMS_MSG_DECODE_RSLT_UNSUPPORTED_VERSION == enDecodeRslt)
        {
            ulCurrFsmId = TAF_XPDS_GetCurrFsmId();
            ulCurState  = TAF_XPDS_GetFsmTopState();

            if ((TAF_XPDS_FSM_L1_MAIN == ulCurrFsmId)
             && (TAF_XPDS_L1_STA_INIT == ulCurState))
            {
                TAF_XPDS_SndXsmsRejNiPosReq(TAF_XPDS_REJ_POS_REASON_VERSION_NOT_SUPPORT);

                TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_SMS_MPC_RL_REJ_POS_REQ);
            }

            return VOS_TRUE;
        }


        /* ����XSMS��Ϣ */
        if (VOS_ERR == TAF_XPDS_ProcXsmsMsg_PreProc(&stXsmsMsg))
        {
            XPDS_ERROR_LOG("TAF_XPDS_RcvXsmsRcvInd_PreProc:TAF_XPDS_XsmsMsgProc error");
        }

    }
    return VOS_TRUE;
}


/****************************************************************************
 �� �� ��  : TAF_XPDS_ProcXsmsMsg
 ��������  : ��������XSMSģ�����Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��17��
    ��    ��   : C00299064
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32  TAF_XPDS_ProcXsmsMsg_PreProc(
    TAF_XPDS_RCV_XSMS_MSG_STRU         *pstXsmsMsg
)
{
    VOS_UINT32                          ulRet;

    switch (pstXsmsMsg->enMsgChoice)
    {
        case TAF_XPDS_RCV_XSMS_MSG_TYPE_NI_POS_REQ:

            ulRet = TAF_XPDS_XsmsNiPosReqHandle_PreProc(&pstXsmsMsg->stXsmsMsgUnion.stPosReq);

            break;

        case TAF_XPDS_RCV_XSMS_MSG_TYPE_CANCEL_NI_TRACK:

            ulRet = TAF_XPDS_XsmsCancelPosHandle_PreProc(&pstXsmsMsg->stXsmsMsgUnion.stCancelNI);

            break;

        case TAF_XPDS_RCV_XSMS_MSG_TYPE_REFRESH_MR_TRACK:

            ulRet = TAF_XPDS_XsmsRefreshMrSessionHandle_PreProc(&pstXsmsMsg->stXsmsMsgUnion.stRefreshMR);

            break;

        default:
            XPDS_ERROR_LOG("TAF_XPDS_XsmsMsgProc:wrong msg type");
            return VOS_ERR;
    }

    return ulRet;

}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_XsmsNiPosReqHandle
 ��������  : ��������XSMSģ�����Ϣ
 �������  : pstXsmsMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��17��
    ��    ��   : C00299064
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32  TAF_XPDS_XsmsNiPosReqHandle_PreProc(
    TAF_XPDS_RCV_XSMS_POS_REQ_STRU     *pstXsmsMsg
)
{
    VOS_UINT32                          ulCurState;

    ulCurState = TAF_XPDS_GetFsmTopState();

    /* �����ǰ�Ѿ��������Ķ�λʵ����ֱ�ӷ���REJ IND */
    if ((TAF_XPDS_FSM_L1_MAIN == TAF_XPDS_GetCurrFsmId())
     && (TAF_XPDS_L1_STA_INIT == ulCurState))
    {
        /* ������Ϣ���ڿ���ȫ�ֱ�����  */
        PS_MEM_CPY(&(TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq),
                   pstXsmsMsg,
                   sizeof(TAF_XPDS_RCV_XSMS_POS_REQ_STRU));

        TAF_XPDS_SndAtGpsNiSessionInd(pstXsmsMsg);

        /* �����ȴ�NI�ظ���ʱ�� */
        TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_GPS_ANSWER_NI_REQ_CNF,
                            TI_TAF_XPDS_WAIT_GPS_ANSWER_NI_REQ_CNF_TIMER_LEN);
    }
    else
    {
        TAF_XPDS_SndXsmsRejNiPosReq(TAF_XPDS_REJ_POS_REASON_IS801_IN_PROCESS);

        TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_SMS_MPC_RL_REJ_POS_REQ);
    }
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_XsmsCancelPosHandle
 ��������  : ��������XSMSģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��17��
    ��    ��   : C00299064
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32  TAF_XPDS_XsmsCancelPosHandle_PreProc(
    TAF_XPDS_RCV_CANCEL_NI_TRACK_STRU *pstXsmsMsg
)
{
    if (pstXsmsMsg->ucCorrlationId == TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.ucCorrelationId)
    {
        if (TAF_XPDS_NI == TAF_XPDS_GetCgpsInitialType())
        {
            TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(TAF_XPDS_PROC_RSLT_XSMS_NI_CANCEL);
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_XsmsRefreshMrSessionHandle
 ��������  : ��������XSMSģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : TAF_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��17��
    ��    ��   : C00299064
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32  TAF_XPDS_XsmsRefreshMrSessionHandle_PreProc(
    TAF_XPDS_RCV_REFRESH_MR_TRACK_STRU    *pstXsmsMsg
)
{
    if (TAF_XPDS_SI != TAF_XPDS_GetCgpsInitialType())
    {
        XPDS_WARNING_LOG("TAF_XPDS_XsmsRefreshMrSessionHandle, current Initial Type is not SI mode ");

        return VOS_OK;
    }

    if (TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_CANCEL == pstXsmsMsg->enCauseCode)
    {
        TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(TAF_XPDS_PROC_RSLT_XSMS_SI_CANCEL);
    }
    else if (TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_LONG_TIME_INACTIVE == pstXsmsMsg->enCauseCode)
    {
        TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(TAF_XPDS_PROC_RSLT_XSMS_SI_LONGINACTIVE);
    }
    else if (TAF_XPDS_REJ_MR_TRACK_CAUSE_CODE_PDE_HANDOFF == pstXsmsMsg->enCauseCode)
    {
        TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(TAF_XPDS_PROC_RSLT_XSMS_SI_REFRESH);
    }
    else
    {
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvTiXpdsIs801SessionExpired_PreProc
 ��������  : Is801��ʱ����ʱ��ת��Ϊ�ڲ�Abort����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��9��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiXpdsIs801SessionExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SndInternalAbnormalAbortAgpsSessionInd(TAF_XPDS_PROC_RSLT_IS801_TIMEOUT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvTiWaitGpsAnswerNiReqExpire_PreProc
 ��������  : �ȴ��ظ�NI����ʱ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��6��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiWaitGpsAnswerNiReqExpire_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    (VOS_VOID)TAF_XPDS_SndXsmsRejNiPosReq(TAF_XPDS_REJ_POS_REASON_POP_UP_SCREEN_TIMER_OUT);

    TAF_XPDS_SndOmGpsSignalMsgInd(NAS_OM_CDMA_GPS_SIGNAL_MSG_TYPE_SMS_MPC_RL_REJ_POS_REQ);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvCasDataInd_PreProc
 ��������  : Ԥ����״̬�յ�CAS DATA IND��Ϣ������
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �Ѵ���
             VOS_FALSE - δ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvCasDschDataInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschDataInd;
    TAF_XPDS_DATA_BURST_MSG_STRU        stDbmMsg;

    PS_MEM_SET(&stDbmMsg, 0, sizeof(TAF_XPDS_DATA_BURST_MSG_STRU));

    pstDschDataInd       = (CAS_CNAS_1X_DSCH_DATA_IND_STRU*)pstMsg;

    if (VOS_ERR == TAF_XPDS_DecodeDataBurstMsg(&stDbmMsg,
                                               pstDschDataInd->aucMsgData))
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvCasDschDataInd_PreProc : TAF_XPDS_DecodeDataBurstMsg ERR");

        return VOS_TRUE;
    }

    /* CP Ĭ��ֻ��NI CP MSA���� */
    TAF_XPDS_GetAgpsCfg()->enCallType   = TAF_XPDS_CTRL_PLANE;
    TAF_XPDS_GetAgpsCfg()->enAgpsType   = TAF_XPDS_NI;
    TAF_XPDS_GetAgpsCfg()->enFixMode    = TAF_XPDS_MSA_MODE;

    TAF_XPDS_ProcForwardPdeMsg_PreProc(stDbmMsg.aucData, stDbmMsg.ucNumFields);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvCasRefLocCnf_PreProc
 ��������  : Ԥ����״̬�յ�CAS DATA IND��Ϣ������
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �Ѵ���
             VOS_FALSE - δ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvCasRefLocCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_XPDS_REF_LOC_CNF_STRU          *pstRefLocCnf;

    pstRefLocCnf  = (CAS_XPDS_REF_LOC_CNF_STRU*)pstMsg;

    if (VOS_OK == pstRefLocCnf->enResult)
    {
        TAF_XPDS_GetPublicDataAddr()->stPilotInfo.usRefPn = pstRefLocCnf->usRefPn;
    }

    return VOS_TRUE;
}




VOS_UINT32 TAF_XPDS_RcvPpmTimerExpire_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SetPpmTimerExpireFlag(VOS_TRUE);

    TAF_XPDS_SndInternalPpmCompleteMsg();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvAtUtsTestStartReq_PreProc
 ��������  : XPDS����ID_AT_XPDS_UTS_TEST_START_REQ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtUtsTestStartReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_MSG_STRU                   *pstAtXpdsMsg;
    VOS_UINT32                          ulDataLen;

    pstAtXpdsMsg = (AT_XPDS_MSG_STRU *)pstMsg;

    /* ����UTSͨ���� */
    TAF_XPDS_SetUtsClientId(pstAtXpdsMsg->stAppCtrl.usClientId);

    ulDataLen = pstAtXpdsMsg->ulLength - sizeof(VOS_UINT32) - sizeof(AT_APPCTRL_STRU);

    TAF_XPDS_SndAtGpsUtsTestStartReq(ulDataLen, pstAtXpdsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvAtGpsPosInfoRsp_PreProc
 ��������  : XPDS����ID_AT_XPDS_GPS_POS_INFO_RSP
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsPosInfoRsp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_GPS_POS_INFO_RSP_STRU      *pstMsgPosInfoRsp;

    /* �ֲ�������ʼ�� */
    pstMsgPosInfoRsp = (AT_XPDS_GPS_POS_INFO_RSP_STRU*)(pstMsg);

    PS_MEM_CPY(&(TAF_XPDS_GetPublicDataAddr()->stCagpsPosInfo),
               &(pstMsgPosInfoRsp->stPosInfo),
               sizeof(AT_XPDS_GPS_POS_INFO_STRU));

    TAF_XPDS_SndAtUtsGpsPosInfo();

    if (VOS_TRUE == TAF_XPDS_GetOmTestFlag())
    {
        TAF_XPDS_SndOmGpsFixRsltInd(NAS_OM_CDMA_GPS_FIX_RSLT_SUCCESS);
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvAtUtsTestStopReq_PreProc
 ��������  : XPDS����ID_AT_XPDS_UTS_TEST_STOP_REQ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��24��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtUtsTestStopReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_MSG_STRU                   *pstAtXpdsMsg;
    VOS_UINT32                          ulDataLen;

    pstAtXpdsMsg = (AT_XPDS_MSG_STRU *)pstMsg;

    ulDataLen = pstAtXpdsMsg->ulLength - sizeof(VOS_UINT32) - sizeof(AT_APPCTRL_STRU);

    TAF_XPDS_SndAtGpsUtsTestStopReq(ulDataLen, pstAtXpdsMsg->aucContent);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvOmStartGpsFixReq_PreProc
 ��������  : XPDS����ID_OM_NAS_CDMA_START_GPS_FIX_REQ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvOmStartGpsFixReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    OM_NAS_CDMA_START_GPS_FIX_REQ_STRU *pstMsgStartReq;
    TAF_XPDS_FIX_MODE_ENUM_UINT8        enXpdsFixMode;
    TAF_XPDS_GPS_START_MODE_ENUM_UINT8  enXpdsStartMode;

    pstMsgStartReq = (OM_NAS_CDMA_START_GPS_FIX_REQ_STRU *)pstMsg;

    TAF_XPDS_SetOmTestFlag(VOS_TRUE);

    TAF_XPDS_SndOmStartGpsFixCnf(pstMsgStartReq);

    if (NAS_OM_CDMA_GPS_FIX_MODE_MONITOR == pstMsgStartReq->enFixMode)
    {
        return VOS_TRUE;
    }

    enXpdsFixMode    = TAF_XPDS_ConvertOmGpsFixModeToXpdsGpsFixMode(pstMsgStartReq->enFixMode);
    enXpdsStartMode  = TAF_XPDS_ConvertOmGpsStartModeToXpdsStartMode(pstMsgStartReq->enStartMode);

    TAF_XPDS_SndAtOmGpsTestStartReq(enXpdsFixMode, enXpdsStartMode);

    if (TAF_XPDS_MSS_MODE == enXpdsFixMode)
    {
        TAF_XPDS_SetAgpsFixMode(TAF_XPDS_MSS_MODE);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvOmStopGpsPosFix_PreProc
 ��������  : XPDS����ID_OM_NAS_CDMA_STOP_GPS_FIX_REQ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : y00174758
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvOmStopGpsFixReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SndOmStopGpsFixCnf((OM_NAS_CDMA_STOP_GPS_FIX_REQ_STRU *)pstMsg);

    TAF_XPDS_SndAtOmGpsTestStopReq();

    TAF_XPDS_SetOmTestFlag(VOS_FALSE);

    if (TAF_XPDS_MSS_MODE == TAF_XPDS_GetAgpsFixMode())
    {
        TAF_XPDS_InitPosCtx();
    }

    return VOS_TRUE;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


