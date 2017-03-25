/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : Rabm_MsgDispatch.c
  Author       : l47619
  Version      : V200R001
  Date         : 2005-08-30
  Description  : ��C�ļ�������MSG_DISPģ���ʵ��
  Function List:
        1. Rabm_TaskEntry
        2. NAS_Rabm2GMsgDispatch

  History      :
  1. Date:2005-08-30
     Author: l47619
     Modification:create
  2. Date        : 2006-05-05
     Author      : l47619
     Modification: �������ⵥ�޸�: A32D03487
  3. Date        : 2006-06-24
     Author      : l47619
     Modification: �������ⵥ�޸�: A32D05709
************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "Rabm2GInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_RABM_MSGDISPATCH_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 Prototype      : NAS_Rabm2GMsgDispatch()
 Description    : 2G�е���Ϣ�ַ�����
 Input          : pMsg                 2G��Ϣ��Ӧ��ָ��
 Output         :
 Return Value   : ��
 Calls          :
 Called By      :
 History        :
  1.Date        : 2005-08-30
    Author      : l47619
    Modification: Created function
  2.Date        : 2006-05-05
    Author      : l47619
    Modification: �������ⵥ�޸�: A32D03487
  3.Date        : 2006-06-24
    Author      : l47619
    Modification: �������ⵥ�޸�: A32D05709
*****************************************************************************/
VOS_VOID  NAS_Rabm2GMsgDispatch(struct MsgCB  *pMsg )
{
    MSG_HEADER_STRU                     *pstHeader;   /*������Ϣͷָ��*/

    if ( VOS_PID_TIMER == pMsg->ulSenderPid )                        /*�յ���ʱ����Ϣ*/
    {
        NAS_RabmTimerExpiredMsgDispatch( ( REL_TIMER_MSG * ) pMsg );
        return;
    }

    pstHeader = ( MSG_HEADER_STRU * )pMsg;                       /*��ȡ��Ϣͷָ��*/

    switch ( pstHeader->ulSenderPid )                            /*����SenderPid�ַ���Ϣ*/
    {
        case   UEPS_PID_SN:                                      /*�յ�SNDCPģ�鷢�͹�������Ϣ*/
            if ( ID_SN_RABM_SEQUENCE_RSP == pstHeader->ulMsgName )
            {
                NAS_RabmSnSequenceRspMsg( ( VOS_VOID *)pMsg );
            }
            else if ( ID_RABM_SNDCP_SAVE_DATA_RSP == pstHeader->ulMsgName )
            {
                NAS_RabmSnSaveDataRspMsg();
            }
            else if ( ID_RABM_SNDCP_RESUME_DATA_RSP == pstHeader->ulMsgName )
            {
                NAS_RabmSnResumeDataRspMsg();
            }
            else
            {
                /*��ӡ������Ϣ---MsgName����:*/
                RABM_LOG_WARNING( "NAS_Rabm2GMsgDispatch:WARNING:The Msg-name of the Msg from UEPS_PID_SN is WRONG!" );
                return;
            }
            break;
        case   WUEPS_PID_TAF:
            if( TAFRABM_PS_DATA_REQ == pstHeader->ulMsgName )
            {
                NAS_RabmRcvTafGprsPsDataReq((TAFRABM_PS_DATA_REQ_STRU *)pMsg);
            }
            else if ( RABM_APS_SET_TRANSMODE_MSG_TYPE == ( ( RABM_APS_SET_TRANSMODE_MSG * )pMsg )->usMsgType )
            {
                NAS_RabmSetTransMode( &( ( ( RABM_APS_SET_TRANSMODE_MSG * )pMsg )->RabmApsSetTransMode ) );
            }
#if (FEATURE_ON == FEATURE_HUAWEI_VP)
            else if (CALL_RABM_VOICEPREFER_CS_EXIST_IND == pstHeader->ulMsgName)
            {
                NAS_RABM_RcvVoicePreferCsExistInd((VOS_VOID *)pMsg);
            }
#endif
            else
            {
                /*��ӡ������Ϣ---MsgName����:*/
                RABM_LOG_WARNING( "NAS_Rabm2GMsgDispatch:WARNING:The Msg-name of the Msg from WUEPS_PID_TAF is WRONG!" );
                return;
            }
            break;
        case   WUEPS_PID_GMM:                                    /*�յ�GMMģ�鷢�͹�������Ϣ*/
            switch ( pstHeader->ulMsgName )
            {
                case ID_GMM_RABM_ROUTING_AREA_UPDATE_IND:
                    NAS_RabmGmmRoutingAreaUpdateIndMsg( ( VOS_VOID * )pMsg );
                    break;
                case ID_GMM_RABM_REESTABLISH_CNF:                    /*�յ�3G����Ϣ*/
                    /*��ӡ������Ϣ---�յ������߼�����Ϣ:*/
                    RABM_LOG_WARNING( "NAS_Rabm2GMsgDispatch:WARNING:RECEIVE ID_GMM_RABM_REESTABLISH_CNF Msg is ILLOGICAL in 2G mode!" );
                    return;
                default:                                         /*�յ���Ϣ���Ƴ������Ϣ*/
                    /*��ӡ������Ϣ---MsgName����:*/
                    RABM_LOG_WARNING( "NAS_Rabm2GMsgDispatch:WARNING:The Msg-name of the Msg from WUEPS_PID_GMM is WRONG!" );
                    return;
            }
            break;
        case   WUEPS_PID_WRR:
            if ( RRRABM_HANDOVER_RAB_IND == pstHeader->ulMsgName )
            {
                NAS_RabmDealHandoverRabInd( (RRRABM_HANDOVER_RAB_IND_STRU *)pMsg );
            }
            else
            {
                /*��ӡ������Ϣ---MsgName����:*/
                RABM_LOG_WARNING( "NAS_Rabm2GMsgDispatch:WARNING:The Msg-name of the Msg from WUEPS_PID_WRR is WRONG!" );
                return;
            }
            break;
        case   WUEPS_PID_PDCP:
            /*��ӡ������Ϣ---�յ������߼�����Ϣ:*/
            RABM_LOG_WARNING( "NAS_Rabm2GMsgDispatch:WARNING:RECEIVE Msg from WUEPS_PID_PDCP is ILLOGICAL in 2G mode!" );
            return;
        case   WUEPS_PID_RLC:
            /*��ӡ������Ϣ---�յ������߼�����Ϣ:*/
            RABM_LOG_WARNING( "NAS_Rabm2GMsgDispatch:WARNING:RECEIVE Msg from WUEPS_PID_RLC is ILLOGICAL in 2G mode!" );
            return;
        default:                                                 /*�յ���Ϣ�ķ���Pid�������Ϣ*/
            /*��ӡ������Ϣ---SendPid����:*/
            RABM_LOG_WARNING( "NAS_Rabm2GMsgDispatch:WARNING:The SendPid of the receive Msg is WRONG!" );
            return;
    }
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
