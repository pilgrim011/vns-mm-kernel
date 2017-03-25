/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaProcImsSmsMsg.c
  Description     : ��C�ļ�ʵ��IMS������Ϣ�����IMS������Ϣ����
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaProcImsSmsMsg.h"
#include "ImsaEntity.h"
#include "ImsaImsInterface.h"
#include "ImsaProcSmsMsg.h"
#include "ImsaPublic.h"


/*lint -e767*/
#define    THIS_FILE_ID         PS_FILE_ID_IMSAPROCIMSSMSMSG_C
#define    THIS_NAS_FILE_ID     NAS_FILE_ID_IMSAPROCIMSSMSMSG_C
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
extern VOS_VOID IMSA_SMS_SndMsgDataInd(const VOS_UINT8* ucData, VOS_UINT32 ulDataLen);
extern VOS_VOID IMSA_SMS_ProcNwSmsReceived(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms);
extern VOS_VOID IMSA_SMS_ProcNwSmsErr(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms);
extern VOS_VOID IMSA_SMS_ProcNwSmsRpError(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms);

extern VOS_UINT32 IMSA_SmsSendIntraResultAction(IMSA_RESULT_ACTION_ENUM_UINT32 enAction);

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name  : IMSA_SMS_SndMsgDataInd()
 Description    : ����Data ind��Ϣ
 Input          : ucData MSG���ݣ�ulDataLen MSG����
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMS_SndMsgDataInd(const VOS_UINT8* ucData, VOS_UINT32 ulDataLen)
{
    IMSA_MSG_DATA_IND_STRU      *pstDataInd;
    VOS_UINT32                   ulMsgDataLen;

    if(ulDataLen < 4)
    {
        ulMsgDataLen = sizeof(IMSA_MSG_DATA_IND_STRU);
    }
    else
    {
        /*lint -e961*/
        ulMsgDataLen = sizeof(IMSA_MSG_DATA_IND_STRU)+ ulDataLen -4;
        /*lint +e961*/
    }

    /*������Ϣ�ռ�*/
    pstDataInd = (VOS_VOID*)IMSA_ALLOC_MSG(ulMsgDataLen);

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstDataInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SMS_SndMsgDataInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SMS_SndMsgDataInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY_BY_NAME(pstDataInd),
                    IMSA_GET_MSG_LENGTH(pstDataInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstDataInd));

    IMSA_WRITE_MSG_MSG_HEAD(pstDataInd,ID_IMSA_MSG_DATA_IND);

    /*���Ž�����ΪPS��*/
    pstDataInd->ucRcvDomain = 0;

    /*��дSMS����*/
    pstDataInd->ulDataLen  = ulDataLen;
    IMSA_MEM_CPY_S(pstDataInd->aucData,ulDataLen,ucData,ulDataLen);

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstDataInd);

}

/*****************************************************************************
 Function Name  : IMSA_SMS_SndMsgReportInd()
 Description    : ����report��Ϣ
 Input          : ucData MSG���ݣ�ulDataLen MSG����
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMS_SndMsgReportInd(VOS_UINT32 ulErrCode,
                                              const VOS_UINT8* pucData,
                                              VOS_UINT32 ulDataLen)
{
    IMSA_MSG_REPORT_IND_STRU    *pstReportInd;

    /*��������*/
    if(ulDataLen > SMR_SMT_RP_USER_DATA_LENGTH)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SMS_SndMsgReportInd:Length is too long!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SMS_SndMsgReportInd_ENUM, LNAS_PARAM_INVALID);
        return ;
    }

    /*������Ϣ�ռ�*/
    pstReportInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_MSG_REPORT_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstReportInd)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SMS_SndMsgReportInd:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SMS_SndMsgReportInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY_BY_NAME(pstReportInd),
                    IMSA_GET_MSG_LENGTH(pstReportInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstReportInd));

    IMSA_WRITE_MSG_MSG_HEAD(pstReportInd,ID_IMSA_MSG_REPORT_IND);

    /*��дSMS����*/
    pstReportInd->enErrorCode           = ulErrCode;

    if(VOS_NULL_PTR != pucData)
    {
        pstReportInd->stRpduData.ulDataLen  = ulDataLen;
        IMSA_MEM_CPY_S(pstReportInd->stRpduData.aucData,ulDataLen,pucData,ulDataLen);
    }

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstReportInd);

}

/*****************************************************************************
 Function Name  : IMSA_SMS_ProcNwSmsErrorInfo()
 Description    : �յ�IMSЭ��ջ�Ķ��Ŵ���ԭ��ֵ�Ĵ�����
 Input          : HICSM_OutputSms  *pstOutSms
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.leixiantiao 00258641      2016-05-13  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMS_ProcNwSmsErrorInfo(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms)
{
    IMSA_INFO_LOG1("IMSA_SMS_ProcNwSmsErrorInfo: process error code", pstOutSms->stErrorCode.usSipStatusCode);
    TLPS_PRINT2LAYER_INFO1(IMSA_SMS_ProcNwSmsErrorInfo_ENUM, LNAS_ERROR, pstOutSms->stErrorCode.usSipStatusCode);

    switch (pstOutSms->stErrorCode.usSipStatusCode)
    {
        /* 504 */
        case IMSA_SIP_NW_ERROR_CAUSE_SERVER_TIMEOUT:

            /* Э��24229��5.1.2A.1.6�й涨, ���յ�504, typeΪrestoration, ��actionδinitial-registraion
               ʱ, ��Ҫ�����ʼע��, �Ҵ��ڶ��PCSCF��ַ��ʱʹ���¸���ַ�Խ���ע�� */
            if (IMSA_IMS_3GPP_TYPE_ACTION_RESTORATION_INIT_REG == pstOutSms->stErrorCode.usIms3gppAction)
            {
                /* ֪ͨService����Restoration���� */
                (VOS_VOID)IMSA_SmsSendIntraResultAction(IMSA_RESULT_ACTION_REG_RESTORATION);
            }
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 Function Name  : IMSA_SMS_ProcNwSmsErr()
 Description    : �յ�IMSЭ��ջ�Ķ��Ŵ���Ĵ�����
 Input          : HICSM_OutputSms  *pstOutSms
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMS_ProcNwSmsErr(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms)
{
    IMSA_SMS_SMR_MO_STRU                *pstSmrMoEntity;
    VOS_UINT32                          ulErrCode;

    pstSmrMoEntity = IMSA_SMS_GetSmrMoEntityAddress();
    if(IMSA_SMS_SMR_STATE_WAIT_FOR_RP_ACK != pstSmrMoEntity->enState)
    {
        IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsErr: Mo entity is not WAIT_FOR_RP_ACK!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsErr_ENUM, 1);
        return;
    }

    /*MOʵ��״̬���п���̬��ֹͣTI_IMSA_SMS_TR1M������ʱ��*/
    pstSmrMoEntity->enState = IMSA_SMS_SMR_STATE_IDLE;

    pstSmrMoEntity->ucMemAvailFlg = IMSA_SMS_FALSE;                   /* ���mem avail��־                        */
    pstSmrMoEntity->ucRetransFlg  = IMSA_SMR_RETRANS_PERMIT;          /* ��λ�ط���־                             */

    IMSA_StopTimer(&pstSmrMoEntity->stTR1MTimer);
    ulErrCode = SMR_SMT_ERROR_IMS_ERROR_BEGIN + pstOutSms->stErrorCode.usSipStatusCode;

    IMSA_SMS_SndMsgReportInd(ulErrCode,VOS_NULL_PTR,0);

    #if (FEATURE_ON == FEATURE_DSDS)
    if ((PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared()) &&
        (IMSA_TASKTYPE_STATUS_NULL != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS)))
    {
        /* ����ӳٻظ���ռ��ʱ����ʱ��Ӧ��ֱ�ӻظ�CNF */
        IMSA_DsdsProcResourceOccupyCnf(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);

        IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);
    }
    #endif

    IMSA_CommonDeregProc();

    /* ��ԭ��ֵ���� */
    IMSA_SMS_ProcNwSmsErrorInfo(pstOutSms);
}

/*****************************************************************************
 Function Name  : IMSA_SMS_ProcNwSmsRpError()
 Description    : �յ�����ظ���RP-ERROR�Ĵ���
 Input          : IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2013-10-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMS_ProcNwSmsRpError(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms)
{
    IMSA_SMS_SMR_MO_STRU                *pstSmrMoEntity;

    IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsRpError: enter.");
    TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsRpError_ENUM, LNAS_ENTRY);

    pstSmrMoEntity = IMSA_SMS_GetSmrMoEntityAddress();

    if(IMSA_SMS_SMR_STATE_WAIT_FOR_RP_ACK != pstSmrMoEntity->enState)
    {
        IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsRpError: Mo entity is not WAIT_FOR_RP_ACK!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsRpError_ENUM, 2);
        return;
    }

    if(pstOutSms->aucMessage[1] != pstSmrMoEntity->ucMessageReference)
    {
        IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsRpError: MR is not equel.");
        TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsRpError_ENUM, 3);
        return;
    }

    /*MOʵ��״̬���п���̬��ֹͣTI_IMSA_SMS_TR1M������ʱ��*/
    pstSmrMoEntity->enState = IMSA_SMS_SMR_STATE_IDLE;
    IMSA_StopTimer(&pstSmrMoEntity->stTR1MTimer);

    if (IMSA_SMS_TRUE == pstSmrMoEntity->ucMemAvailFlg )
    {
        /* �˹�����mem avail����                    */
        /* �Դ���ԭ��ֵ�Ĵ����ο�GU����ʵ�֣���Э��Ҫ����#41ʱ���ش�RP-SMMA�Ļ����ϣ�
        ������ԭ��ֵΪ#42��47,38ʱ�ش�RP-SMMA */
        if ((IMSA_SMR_ERR_CAUSE_TEMP_FAILURE   == pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET])
            || (IMSA_SMR_ERR_CAUSE_CONGESTION  == pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET])
            || (IMSA_SMR_ERR_CAUSE_RES_UNAVAIL == pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET])
            || (IMSA_SMR_ERR_CAUSE_NET_OUT_OF_ORDER == pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET]))
        {                                                               /* ��temporary error                        */
            IMSA_SMS_MemNotifyRetrans(SMR_SMT_ERROR_RP_ERROR_BEGIN|pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET]);         /* �����ط����̵Ĵ���                       */
        }
        else
        {
            /*��������RP ERR��������Я���Ĵ�����*/
            IMSA_SMS_SndMsgReportInd(SMR_SMT_ERROR_RP_ERROR_BEGIN|pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET],
                                       (VOS_UINT8*)pstOutSms->aucMessage,\
                                        pstOutSms->ucMessageLen);
            pstSmrMoEntity->ucMemAvailFlg = IMSA_SMS_FALSE;                   /* ���mem avail��־                        */
            pstSmrMoEntity->ucRetransFlg  = IMSA_SMR_RETRANS_PERMIT;          /* ��λ�ط���־                             */
            pstSmrMoEntity->enState = IMSA_SMS_SMR_STATE_IDLE;                                      /* ״̬Ǩ�Ƶ�����״̬                       */

            #if (FEATURE_ON == FEATURE_DSDS)
            if ((PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared()) &&
                (IMSA_TASKTYPE_STATUS_NULL != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS)))
            {
                /* ����ӳٻظ���ռ��ʱ����ʱ��Ӧ��ֱ�ӻظ�CNF */
                IMSA_DsdsProcResourceOccupyCnf(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);

                IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);
            }
            #endif

            IMSA_CommonDeregProc();
        }
    }
    else
    {
        /*��������RP ERR��������Я���Ĵ�����*/
        IMSA_SMS_SndMsgReportInd(SMR_SMT_ERROR_RP_ERROR_BEGIN|pstOutSms->aucMessage[IMSA_SMS_RP_ERROR_OFFSET],
                           (VOS_UINT8*)pstOutSms->aucMessage,\
                            pstOutSms->ucMessageLen);

        #if (FEATURE_ON == FEATURE_DSDS)
        if (PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared())
        {
            /* ����ӳٻظ���ռ��ʱ����ʱ��Ӧ��ֱ�ӻظ�CNF */
            IMSA_DsdsProcResourceOccupyCnf(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);

            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);
        }
        #endif

        IMSA_CommonDeregProc();
    }
}


/*****************************************************************************
 Function Name  : IMSA_SMS_ProcNwSmsReceived()
 Description    : �յ�����Ķ������ݵĴ�����
 Input          : HICSM_OutputSms  *pstOutSms
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-08-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMS_ProcNwSmsReceived(const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms)
{
    IMSA_SMS_SMR_MO_STRU                *pstSmrMoEntity;
    IMSA_SMS_SMR_MT_STRU                *pstSmrMtEntity;

    /*������Ϣ���ʹ���*/
    switch(pstOutSms->aucMessage[0])
    {
    /*MT RP Data*/
    case IMSA_SMS_NTM_DATA_TYPE_RP_DATA:
        pstSmrMtEntity = IMSA_SMS_GetSmrMtEntityAddress();
        if(pstSmrMtEntity->enState != IMSA_SMS_SMR_STATE_IDLE)
        {
            IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsReceived: Mt entity is not idle!");
            TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsReceived_ENUM, 1);
            break;
        }
        switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS))
        {
            case IMSA_RESOURCE_STATUS_ACTIVE:

                /*MT���ţ�MTʵ��ת״̬������MR������TI_IMSA_SMS_TR2M��ʱ��*/
                pstSmrMtEntity->enState = IMSA_SMS_SMR_STATE_WAIT_TO_SND_RP_ACK;
                pstSmrMtEntity->ucMessageReference = (VOS_UINT8)pstOutSms->aucMessage[1];
                IMSA_StartTimer(&pstSmrMtEntity->stTimerInfo);

                /*�������ݷ���MSG*/
                IMSA_SMS_SndMsgDataInd((VOS_UINT8*)pstOutSms->aucMessage,\
                                        pstOutSms->ucMessageLen);
                break;

            #if (FEATURE_ON == FEATURE_DSDS)
            case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

                IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS,
                                              IMSA_RF_RES_APPLY_TRIGER_SRC_SMMA_RETRANS,
                                              VOS_FALSE,
                                              VOS_FALSE);

                /*MT���ţ�MTʵ��ת״̬������MR������TI_IMSA_SMS_TR2M��ʱ��*/
                pstSmrMtEntity->enState = IMSA_SMS_SMR_STATE_WAIT_TO_SND_RP_ACK;
                pstSmrMtEntity->ucMessageReference = (VOS_UINT8)pstOutSms->aucMessage[1];
                IMSA_StartTimer(&pstSmrMtEntity->stTimerInfo);

                /*�������ݷ���MSG*/
                IMSA_SMS_SndMsgDataInd((VOS_UINT8*)pstOutSms->aucMessage,\
                                        pstOutSms->ucMessageLen);
                break;

            case  IMSA_RESOURCE_STATUS_NULL:

                IMSA_DsdsProcResourceApplyReq(RRM_PS_TASK_TYPE_LTE_IMS_MT_SMS,
                                              IMSA_RF_RES_APPLY_TRIGER_SRC_MT_SMS,
                                              VOS_FALSE,
                                              VOS_TRUE);

                IMSA_DsdsSaveMtSmsMsg(pstOutSms);
                break;
            #endif
            default:
                break;

        }
        break;

    /*MO RP ACK*/
    case IMSA_SMS_NTM_DATA_TYPE_RP_ACK:
        pstSmrMoEntity = IMSA_SMS_GetSmrMoEntityAddress();
        if(IMSA_SMS_SMR_STATE_WAIT_FOR_RP_ACK != pstSmrMoEntity->enState)
        {
            IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsReceived: Mo entity is not WAIT_FOR_RP_ACK!");
            TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsReceived_ENUM, 2);
            break;
        }

        if(pstOutSms->aucMessage[1] != pstSmrMoEntity->ucMessageReference)
        {
            IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsReceived: MR is not equel.");
            TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsReceived_ENUM, 3);
            break;
        }

        /*MOʵ��״̬���п���̬��ֹͣTI_IMSA_SMS_TR1M������ʱ��*/
        pstSmrMoEntity->enState = IMSA_SMS_SMR_STATE_IDLE;
        IMSA_StopTimer(&pstSmrMoEntity->stTR1MTimer);

        if (IMSA_SMS_TRUE == pstSmrMoEntity->ucMemAvailFlg)
        {                                                                   /* �˹�����mem avail����                    */
            pstSmrMoEntity->ucMemAvailFlg = IMSA_SMS_FALSE;                       /* ���mem avail��־                        */
            pstSmrMoEntity->ucRetransFlg  = IMSA_SMR_RETRANS_PERMIT;              /* ��λ�ط���־                             */
        }

        IMSA_SMS_SndMsgReportInd(SMR_SMT_ERROR_NO_ERROR,
                           (VOS_UINT8*)pstOutSms->aucMessage,\
                            pstOutSms->ucMessageLen);

        #if (FEATURE_ON == FEATURE_DSDS)
        if ((PS_RRM_RF_SHARED == IMSA_Dsds_RRM_RfResourceIsShared()) &&
            (IMSA_TASKTYPE_STATUS_NULL != IMSA_DsdsGetTaskStatusByTaskType(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS)))
        {
            /* ����ӳٻظ���ռ��ʱ����ʱ��Ӧ��ֱ�ӻظ�CNF */
            IMSA_DsdsProcResourceOccupyCnf(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);

            IMSA_DsdsProcResourceRelease(RRM_PS_TASK_TYPE_LTE_IMS_MO_SMS);
        }
        #endif

        IMSA_CommonDeregProc();
        break;

    case IMSA_SMS_NTM_DATA_TYPE_RP_ERR:
        IMSA_SMS_ProcNwSmsRpError(pstOutSms);
        break;

    default:
        IMSA_WARN_LOG("IMSA_SMS_ProcNwReportReceived: Msg Type ERR.");
        TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsReceived_ENUM, LNAS_MSG_INVALID);
        break;
    }


}

/*****************************************************************************
 Function Name  : IMSA_D2ImsMsgSmsEvent()
 Description    : D2IMS�������͵��¼�������
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-21  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ImsMsgSmsEvent(VOS_VOID *pSmsEvent)
{
    IMSA_IMS_OUTPUT_SMS_EVENT_STRU       *pstOutSms;

    pstOutSms = (IMSA_IMS_OUTPUT_SMS_EVENT_STRU*)pSmsEvent;

    if(IMSA_IMS_OUTPUT_SMS_REASON_SMS_RECEIVED == pstOutSms->enOutputSmsReason)
    {
        IMSA_SMS_ProcNwSmsReceived(pstOutSms);
    }
    /*������Ϣ�ظ�*/
    else if(IMSA_IMS_OUTPUT_SMS_REASON_OK == pstOutSms->enOutputSmsReason)
    {
        IMSA_INFO_LOG("IMSA_ImsMsgSmsEvent: Receive OK!");
        TLPS_PRINT2LAYER_INFO(IMSA_SMS_ProcNwSmsReceived_ENUM, 2);
    }
    /*������*/
    else if(IMSA_IMS_OUTPUT_SMS_REASON_ERROR == pstOutSms->enOutputSmsReason)
    {
        IMSA_SMS_ProcNwSmsErr(pstOutSms);
    }
    else
    {
    }

}
#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 Function Name  : IMSA_SMSProcMoResourceApplyCnf
 Discription    : ����MO SMS��Դ��ʱ����ʱ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-23  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SMSProcMtResourceApplyCnf
(
    const IMSA_IMS_OUTPUT_SMS_EVENT_STRU  *pstOutSms
)
{
    IMSA_SMS_SMR_MT_STRU                *pstSmrMtEntity;

    pstSmrMtEntity = IMSA_SMS_GetSmrMtEntityAddress();
    if(pstSmrMtEntity->enState != IMSA_SMS_SMR_STATE_IDLE)
    {
        IMSA_WARN_LOG("IMSA_SMS_ProcNwSmsReceived: Mt entity is not idle!");
        TLPS_PRINT2LAYER_WARNING(IMSA_SMS_ProcNwSmsReceived_ENUM, 1);
    }

    /*MT���ţ�MTʵ��ת״̬������MR������TI_IMSA_SMS_TR2M��ʱ��*/
    pstSmrMtEntity->enState = IMSA_SMS_SMR_STATE_WAIT_TO_SND_RP_ACK;
    pstSmrMtEntity->ucMessageReference = (VOS_UINT8)pstOutSms->aucMessage[1];
    IMSA_StartTimer(&pstSmrMtEntity->stTimerInfo);

    /*�������ݷ���MSG*/
    IMSA_SMS_SndMsgDataInd((VOS_UINT8*)pstOutSms->aucMessage,\
                            pstOutSms->ucMessageLen);

    return;
}
#endif


#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaProcImsSmsMsg.c */



