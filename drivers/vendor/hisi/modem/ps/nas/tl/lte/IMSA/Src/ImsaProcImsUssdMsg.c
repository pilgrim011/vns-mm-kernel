/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaProcImsUssdMsg.c
  Description     : ��C�ļ�ʵ���յ�IMS��USSD��Ϣ����͸�SPM��Ϣ����
  History           :
     1.leili 00132387      2013-12-27  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaProcImsUssdMsg.h"
#include "ImsaEntity.h"
#include "ImsaPublic.h"
#include "ImsaProcUssdMsg.h"

/*lint -e767*/
#define    THIS_FILE_ID       PS_FILE_ID_IMSAPROCIMSUSSDMSG_C
#define    THIS_NAS_FILE_ID   NAS_FILE_ID_IMSAPROCIMSUSSDMSG_C
/*lint +e767*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/


/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name  : IMSA_ImsMsgUssdEvent()
 Description    : IMS USSD ���͵��¼�������
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID
History        :
      1.l00132387   2013-12-23  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ImsMsgUssdEvent(VOS_VOID *pUssdEvent)
{
    IMSA_IMS_OUTPUT_USSD_EVENT_STRU *pstOutUssd = VOS_NULL_PTR;

    pstOutUssd = (IMSA_IMS_OUTPUT_USSD_EVENT_STRU*)pUssdEvent;

    /*lint -e788*/
    switch (pstOutUssd->enOutputUssdReason)
    {
        case IMSA_IMS_OUTPUT_USSD_REASON_OK:
            IMSA_ProcImsMsgUssdReasonOk(pstOutUssd);
            break;
        case IMSA_IMS_OUTPUT_USSD_REASON_NOTIFY_EVENT:
            IMSA_ProcImsMsgUssdReasonNotify(pstOutUssd);
            break;
        case IMSA_IMS_OUTPUT_USSD_REASON_REQUEST_EVENT:
            IMSA_ProcImsMsgUssdReasonRequest(pstOutUssd);
            break;
        case IMSA_IMS_OUTPUT_USSD_REASON_DISCONNECT_EVENT:
            IMSA_ProcImsMsgUssdReasonDisconnect(pstOutUssd);
            break;
        case IMSA_IMS_OUTPUT_USSD_REASON_ERROR:
            IMSA_ProcImsMsgUssdReasonError(pstOutUssd);
            break;
        default:
            IMSA_INFO_LOG("IMSA_ImsMsgUssdEvent: reason is err");
            TLPS_PRINT2LAYER_INFO(IMSA_ImsMsgUssdEvent_ENUM, LNAS_PARAM_INVALID);
            break;

    }/*lint +e788*/
}

/*****************************************************************************
 Function Name  : IMSA_ProcImsMsgUssdReasonOk()
 Description    : �յ�IMS USSD REASON OK�Ĵ�����
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.l00132387   2013-12-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcImsMsgUssdReasonOk(IMSA_IMS_OUTPUT_USSD_EVENT_STRU *pstOutUssdEvt)
{
    IMSA_USSD_MANAGER_STRU              *pstUssdManager;

    IMSA_INFO_LOG("IMSA_ProcImsMsgUssdReasonOk is entered");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgUssdReasonOk_ENUM, LNAS_ENTRY);

    (void)pstOutUssdEvt;
    pstUssdManager = IMSA_USSD_GetEntityAddress();

    if (IMSA_USSD_MO_CONN_STATE == pstUssdManager->enUssdState)
    {

       (VOS_VOID)IMSA_SendSpmUssdDataSndEvt(pstUssdManager->usClientId,
                                    pstUssdManager->ucOpId);
    }
    return;
}

/*****************************************************************************
 Function Name  : IMSA_ProcImsMsgUssdReasonNotify()
 Description    : �յ�IMS USSD REASON NOTIFY�Ĵ�����
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.l00132387   2013-12-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcImsMsgUssdReasonNotify(const IMSA_IMS_OUTPUT_USSD_EVENT_STRU *pstOutUssdEvt)
{
    IMSA_USSD_MANAGER_STRU              *pstUssdManager;
    TAF_SS_USSD_STRING_STRU             stUssdString = {0};

    IMSA_INFO_LOG("IMSA_ProcImsMsgUssdReasonNotify is entered");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgUssdReasonNotify_ENUM, LNAS_ENTRY);

    pstUssdManager = IMSA_USSD_GetEntityAddress();

    if (IMSA_USSD_MT_CONN_STATE == pstUssdManager->enUssdState)
    {
        IMSA_INFO_LOG("IMSA_ProcImsMsgUssdReasonNotify:state is err");
        TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgUssdReasonNotify_ENUM, IMSA_STATE_ERROR);
        return;
    }

    stUssdString.usCnt = pstOutUssdEvt->usMessageLen;
    IMSA_MEM_CPY_S(                 stUssdString.aucUssdStr,
                                    sizeof(stUssdString.aucUssdStr),
                                    pstOutUssdEvt->aucMessage,
                                    pstOutUssdEvt->usMessageLen);

    if (IMSA_USSD_MO_CONN_STATE == pstUssdManager->enUssdState)
    {
        /*ֹͣ�ȴ�������Ӧ��ʱ��*/
        IMSA_StopTimer(&(pstUssdManager->stUssdWaitNetRspTimer));

        (VOS_VOID)IMSA_SendSpmUssdNotifyIndEvt(  pstUssdManager->usClientId,
                                    pstUssdManager->ucOpId,
                                    pstOutUssdEvt->encType,
                                    &stUssdString);
    }
    else
    {
        /*USSD��״̬IMSA_USSD_IDLE_STATE�Ĵ���*/
        /*����������������*/
        (VOS_VOID)IMSA_SendSpmUssdNotifyIndEvt(  0x3fff,
                                        0,
                                    pstOutUssdEvt->encType,
                                    &stUssdString);
    }


    /*�����ȴ�APP��Ӧ��ʱ��*/
    IMSA_StartTimer(&(pstUssdManager->stUssdWaitAppRspTimer));
    pstUssdManager->enUssdState = IMSA_USSD_MT_CONN_STATE;

    return;
}

/*****************************************************************************
 Function Name  : IMSA_ProcImsMsgUssdReasonRequest()
 Description    : �յ�IMS USSD REASON REQUEST�Ĵ�����
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.l00132387   2013-12-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcImsMsgUssdReasonRequest(const IMSA_IMS_OUTPUT_USSD_EVENT_STRU *pstOutUssdEvt)
{
    IMSA_USSD_MANAGER_STRU              *pstUssdManager;
    TAF_SS_USSD_STRING_STRU             stUssdString = {0};

    IMSA_INFO_LOG("IMSA_ProcImsMsgUssdReasonRequest is entered");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgUssdReasonRequest_ENUM, LNAS_ENTRY);

    pstUssdManager = IMSA_USSD_GetEntityAddress();

    if (IMSA_USSD_MT_CONN_STATE == pstUssdManager->enUssdState)
    {
        IMSA_INFO_LOG("IMSA_ProcImsMsgUssdReasonRequest:state is err");
        TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgUssdReasonRequest_ENUM, IMSA_STATE_ERROR);
        return;
    }

    stUssdString.usCnt = pstOutUssdEvt->usMessageLen;
    IMSA_MEM_CPY_S(                 stUssdString.aucUssdStr,
                                    sizeof(stUssdString.aucUssdStr),
                                    pstOutUssdEvt->aucMessage,
                                    pstOutUssdEvt->usMessageLen);

    if (IMSA_USSD_MO_CONN_STATE == pstUssdManager->enUssdState)
    {
        /*ֹͣ�ȴ�������Ӧ��ʱ��*/
        IMSA_StopTimer(&(pstUssdManager->stUssdWaitNetRspTimer));

        (VOS_VOID)IMSA_SendSpmUssdReqIndEvt(  pstUssdManager->usClientId,
                                    pstUssdManager->ucOpId,
                                    pstOutUssdEvt->encType,
                                    &stUssdString);
    }
    else
    {
        /*USSD��״̬IMSA_USSD_IDLE_STATE�Ĵ���*/
        /*����������������*/
        (VOS_VOID)IMSA_SendSpmUssdReqIndEvt(  0x3fff,
                                        0,
                                    pstOutUssdEvt->encType,
                                    &stUssdString);
    }


    /*�����ȴ�APP��Ӧ��ʱ��*/
    IMSA_StartTimer(&(pstUssdManager->stUssdWaitAppRspTimer));
    pstUssdManager->enUssdState = IMSA_USSD_MT_CONN_STATE;

    return;
}

/*****************************************************************************
 Function Name  : IMSA_ProcImsMsgUssdReasonDisconnect()
 Description    : �յ�IMS USSD REASON DISCONNECT�Ĵ�����
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.l00132387   2013-12-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcImsMsgUssdReasonDisconnect(IMSA_IMS_OUTPUT_USSD_EVENT_STRU *pstOutUssdEvt)
{
    IMSA_USSD_MANAGER_STRU              *pstUssdManager;

    IMSA_INFO_LOG("IMSA_ProcImsMsgUssdReasonDisconnect is entered");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgUssdReasonDisconnect_ENUM, LNAS_ENTRY);

    pstUssdManager = IMSA_USSD_GetEntityAddress();
    (void)pstOutUssdEvt;

    if (IMSA_USSD_IDLE_STATE == pstUssdManager->enUssdState)
    {
        IMSA_INFO_LOG("IMSA_ProcImsMsgUssdReasonDisconnect:state is err");
        TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgUssdReasonDisconnect_ENUM, IMSA_STATE_ERROR);
        return;
    }

    if (IMSA_USSD_MO_CONN_STATE == pstUssdManager->enUssdState)
    {
        /*ֹͣ�ȴ�������Ӧ��ʱ��*/
        IMSA_StopTimer(&(pstUssdManager->stUssdWaitNetRspTimer));

        (VOS_VOID)IMSA_SendSpmUssdRelCompleteIndEvt(  pstUssdManager->usClientId,
                                    pstUssdManager->ucOpId);

    }
    else
    {
        /*USSD��״̬IMSA_USSD_MT_CONN_STATE�Ĵ���*/
        /*ֹͣ�ȴ�APP��Ӧ��ʱ��*/
        IMSA_StopTimer(&(pstUssdManager->stUssdWaitAppRspTimer));

        (VOS_VOID)IMSA_SendSpmUssdRelCompleteIndEvt( 0x3fff,
                                    0);
    }

    pstUssdManager->enUssdState = IMSA_USSD_IDLE_STATE;

    return;
}

/*****************************************************************************
 Function Name  : IMSA_ProcImsMsgUssdReasonError()
 Description    : �յ�IMS USSD REASON ERROR�Ĵ�����
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.l00132387   2013-12-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcImsMsgUssdReasonError(const IMSA_IMS_OUTPUT_USSD_EVENT_STRU *pstOutUssdEvt)
{
    IMSA_USSD_MANAGER_STRU              *pstUssdManager;

    IMSA_INFO_LOG("IMSA_ProcImsMsgUssdReasonError is entered");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgUssdReasonError_ENUM, LNAS_ENTRY);

    pstUssdManager = IMSA_USSD_GetEntityAddress();

    if (IMSA_USSD_MO_CONN_STATE != pstUssdManager->enUssdState)
    {
        IMSA_INFO_LOG("IMSA_ProcImsMsgUssdReasonError: state is err");
        TLPS_PRINT2LAYER_INFO(IMSA_ProcImsMsgUssdReasonError_ENUM, IMSA_STATE_ERROR);
        return;
    }

    /*ֹͣ�ȴ�������Ӧ��ʱ��*/
    IMSA_StopTimer(&(pstUssdManager->stUssdWaitNetRspTimer));

    /*IMS���ص��µĴ����ȷ�Ϻ����*/
    if ((300 > pstOutUssdEvt->stErrorCode.usSipStatusCode) || (699 < pstOutUssdEvt->stErrorCode.usSipStatusCode))
    {
        /*IMS���ص��µ�ʧ��*/
        (VOS_VOID)IMSA_SendSpmUssdErrorEvt(  pstUssdManager->usClientId,
                                    pstUssdManager->ucOpId,
                                    pstOutUssdEvt->stErrorCode.usSipStatusCode + TAF_ERR_SS_IMSA_BASE);
    }
    else
    {
        /*���ർ�µ�ʧ��*/
        /*(VOS_VOID)IMSA_SendSpmUssdReqCnfEvt(   pstUssdManager->usClientId,
                                    pstUssdManager->ucOpId,
                                    (VOS_UINT8)pstOutUssdEvt->stErrorCode.usSipStatusCode);*/
        (VOS_VOID)IMSA_SendSpmUssdErrorEvt(  pstUssdManager->usClientId,
                                    pstUssdManager->ucOpId,
                                    pstOutUssdEvt->stErrorCode.usSipStatusCode + TAF_ERR_SS_IMS_BASE);
    }

    pstUssdManager->enUssdState = IMSA_USSD_IDLE_STATE;

    return;
}


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaProcImsUssdMsg.c */









